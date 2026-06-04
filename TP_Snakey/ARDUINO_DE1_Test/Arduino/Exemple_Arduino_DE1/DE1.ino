//==========================================================================
// Fonctions d'accès au bus de données et d'adresse de la carte Arduino_DE1
// - Bus d'adresse de 2 bits
// - Bus de données de 8 bits (bidirectionnel)
// - READ : actif à '0'  (initialisé à 1 par défaut)
// - WRITE : actif à '0'  (initialisé à 1 par défaut)
//
// V1.1  
// FC
//===========================================================================

// ==========================
//   Principe d'utilisation
// ==========================
//
//  1) Initialisation:
//
//     Appeler "initDE1_Arduino();" dans la fonction "setup()"
//
//  2) Ecrire un mot à une adresse:
//
//     void writeData( char p_address, unsigned char p_data);
//         p_address: adresse de 0 à 3
//         p_data: valeur à écrire (octet)
//
//  3) Lire un mot à une adresse
//
//     unsigned char readData( char p_address);
//         p_address: adresse de 0 à 3
//         valeur de retour: valeur lue (octet)
//


// Pour mémoire:
//  - Environ 100us de temps de propagation
//  - Auto-mémorisation sur le bus de données lorsque les deux périphériques sont en tri-state.

#define DELAY_DE1 150  // prise en compte du temps de propagation (en us)

// Définition des signaux/broches Arduino
#define READ 13
#define WRITE 12
#define BUS_A0 11
#define BUS_A1 10
#define BUS_D0 9
#define BUS_D1 8
#define BUS_D2 7
#define BUS_D3 6
#define BUS_D4 5
#define BUS_D5 4
#define BUS_D6 3
#define BUS_D7 2

// Modifie l'adresse du bus d'adresse
// p_address: 0, 1, 2 ou 3
void setAddress( char p_address )
{
  digitalWrite(BUS_A0, ((p_address&0x01)==0x00)?LOW:HIGH);
  digitalWrite(BUS_A1, ((p_address&0x02)==0x00)?LOW:HIGH);
}

// Ecrit un mot à une adresse
// p_address: 0, 1, 2 ou 3
void writeData( char p_address, unsigned char p_data)
{
  //Modifie le bus d'adresse  
  setAddress(p_address);
  //Active le Bus de données
  pinMode(BUS_D0, OUTPUT);
  pinMode(BUS_D1, OUTPUT);
  pinMode(BUS_D2, OUTPUT);
  pinMode(BUS_D3, OUTPUT);
  pinMode(BUS_D4, OUTPUT);
  pinMode(BUS_D5, OUTPUT);
  pinMode(BUS_D6, OUTPUT);
  pinMode(BUS_D7, OUTPUT);
  //Ecrit la nouvelle valeur du bus de données
  digitalWrite(BUS_D0, ((p_data&0x01)==0x01));
  digitalWrite(BUS_D1, ((p_data&0x02)==0x02));
  digitalWrite(BUS_D2, ((p_data&0x04)==0x04));
  digitalWrite(BUS_D3, ((p_data&0x08)==0x08));
  digitalWrite(BUS_D4, ((p_data&0x10)==0x10));
  digitalWrite(BUS_D5, ((p_data&0x20)==0x20));
  digitalWrite(BUS_D6, ((p_data&0x40)==0x40));
  digitalWrite(BUS_D7, ((p_data&0x80)==0x80));
  // Attend le temps de propagation du bus de donnée 
  delayMicroseconds(DELAY_DE1);
  //Active l'écriture
  digitalWrite(WRITE, LOW );
  // Active le WRITE pendant DELAY_DE1 us
  delayMicroseconds(DELAY_DE1);
  //Désactive l'écriture
  digitalWrite(WRITE, HIGH );
  // Remet le bus de données en haute impédance
  pinMode(BUS_D0, INPUT);
  pinMode(BUS_D1, INPUT);
  pinMode(BUS_D2, INPUT);
  pinMode(BUS_D3, INPUT);
  pinMode(BUS_D4, INPUT);
  pinMode(BUS_D5, INPUT);
  pinMode(BUS_D6, INPUT);
  pinMode(BUS_D7, INPUT);
}


// Lit un mot à une adresse
// p_address: adresse de 0 à 3
// Retourne la valeur lue sur le bus de données
unsigned char readData( char p_address)
{
  unsigned char l_val;

  //Modifie le bus d'adresse
  setAddress(p_address);  
  // Active la lecture
  digitalWrite(READ, LOW );  
  // Attend le temps de propagation du bus de donnée 
  delayMicroseconds(DELAY_DE1);
  //Lit les données sur le bus de données
  l_val=(digitalRead(BUS_D7)<<7)|(digitalRead(BUS_D6)<<6)|(digitalRead(BUS_D5)<<5)|(digitalRead(BUS_D4)<<4)
        |(digitalRead(BUS_D3)<<3)|(digitalRead(BUS_D2)<<2)|(digitalRead(BUS_D1)<<1)|(digitalRead(BUS_D0));
 // Désactive la lecture
  digitalWrite(READ, HIGH );         
  return l_val;        
}

// Configure les broches de la carte Arduino
// et applique les états par défaut
void initDE1_Arduino(void)
{
  // READ: sortie à 0 par défaut
  pinMode(READ, OUTPUT);
  digitalWrite(READ, HIGH);
  // READ: sortie à 0 par défaut
  pinMode(WRITE, OUTPUT);
  digitalWrite(WRITE, HIGH);
  // Bus d'adresse A1 A0
  // => sorties à 0 par défaut
  pinMode(BUS_A0, OUTPUT);
  digitalWrite(BUS_A0, LOW);
  pinMode(BUS_A1, OUTPUT);
  digitalWrite(BUS_A1, LOW);

  //Bus de données en haute impédance par défaut
  pinMode(BUS_D0, INPUT);
  pinMode(BUS_D1, INPUT);
  pinMode(BUS_D2, INPUT);
  pinMode(BUS_D3, INPUT);
  pinMode(BUS_D4, INPUT);
  pinMode(BUS_D5, INPUT);
  pinMode(BUS_D6, INPUT);
  pinMode(BUS_D7, INPUT);
}
