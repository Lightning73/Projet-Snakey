//==================================================================
// Programme d'exemple de lecture/écriture avec la carte ARDUINO_DE1
//  
// Pour la documentation, voir l'onglet "DE1".
//==================================================================

// Broches du joystick
const int pin1X = A0;
const int pin1Y = A1;

int prevX = 128;
int prevY = 128;


void setup() 
{
  Serial.begin(9600);      // Ouverture du port série à 9600 baud 

  Serial.println("Exemple écriture/lecture sur la carte ARDUINO_DE1");

  //Initialisation de la carte ARDUINO_DE1
  initDE1_Arduino();

  // Initialisation des 4 registres
  for (int i=0;i<=3;i++)
  {  
    //Ecriture de 0 à l'adresse "i"
    writeData( i, 0);
  }
}

void loop() 
{
  unsigned char l_value;

  // Lecture des axes
  int xValue = analogRead(pin1X);
  int yValue = analogRead(pin1Y);

  // resize 8bit
  xValue = xValue >> 2;
  yValue = yValue >> 2;

  // Bloque le droite-gauche / haut-bas
  if((96 > xValue && prevX > 128) || (96 > prevX && xValue > 128))
  {
    xValue = 128;
  }
  if((96 > yValue && prevY > 128) || (96 > prevY && yValue > 128))
  {
    yValue = 128;
  }

  int count = 0;
  if(96 > xValue || xValue > 160) count ++;
  if(96 > yValue || yValue > 160) count ++;
     
  // Récupère l'ancienne valeure si point nul
  if(count != 1)
     {
      xValue = prevX;
      yValue = prevY;
     }

 

     
  // Lecture du bouton

  //Lecture du registre à l'adresse 0
  l_value=readData(0);

  // cast du signal 8 bits (0–255)
  unsigned char x1_low  = xValue & 0xFF;        // 8 bits faibles

  unsigned char x2_low  = yValue & 0xFF;        // 8 bits faibles

  // écriture sur 2 registres
  writeData(0, x1_low);   // bits 0–7

  // écriture sur 2 registres
  writeData(1, x2_low);   // bits 0–7
   

  // Envoi des données sur le port série
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print("/");
  Serial.print(prevX);

  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print("/");
  Serial.print(prevY);
  Serial.println("");

  prevX = xValue;
  prevY = yValue;

  // Pause de 500ms
  delay(10);
  }
  // */
