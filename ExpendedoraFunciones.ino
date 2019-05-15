#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>9
#include <Keypad.h>

//Teclado matricial
const byte FILAS = 2;
const byte COLUMNAS = 2;
char keys[FILAS] [COLUMNAS] = {
  {'1','2'},
  {'3','4'}
};

//Establezco los pines de entrada del teclado.
byte pinesFilas[FILAS] = {9,8};
byte pinesColumnas[COLUMNAS] ={10,11};

//Inicializo el teclado
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// Inicializo la pantalla lcd
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

//Introduzco variables
char tecla;
int coin, vueltas, monedas;
byte choco, latas, num=0, pin;

void Cambiar(int);
void Agotado(int);
void Cinco();
void Agradecer();
void Darcambio (int);
void Registro(int, int);//No estoy seguro de esta chapuza
void Motores(int);

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);//Motor para el producto 1.
  pinMode(12,OUTPUT);//Motor para el producto 2.
  pinMode(3, OUTPUT);//LED que actua como mecanismo de cambio.
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  tecla ='0';
  monedas=0;
  choco=2, latas=2;
}

void loop() 
{
   //Nos aseguramos que la moneda se haya introducido, contamos con que el precio es la moneda minima
   lcd.clear();
   do
    {
     lcd.print("Introduzca");
     lcd.setCursor(0,1);
     lcd.print("monedas");
     lcd.setCursor(0,0);
     if (Serial.available()>0)
    {
        lcd.clear();
        coin=Serial.read();
        if (coin > 10) 
        {
            monedas=coin-'0';
            lcd.clear();
            lcd.print("Ha introducido");
            lcd.setCursor(7,1);
            lcd.print(monedas);
            delay(3000);
            lcd.clear();
            if (monedas<5)
              {
                Agotado (monedas);
                lcd.print("Saldo");
                lcd.setCursor(0,1);
                lcd.print("insuficiente");
                lcd.setCursor(1,0);
                delay(3000);
                lcd.clear();
              }
        }
    }

   }while((monedas<=4)||(monedas>9));
    
    lcd.clear();
    lcd.print("Seleccione");
    lcd.setCursor(0,1);
    lcd.print("su compra");
    lcd.setCursor(0,0);
    delay(1000);
    do
    { 
      tecla = teclado.getKey();
    } while (tecla <'1' || tecla >'4');
    Serial.print(tecla);
    switch (tecla)
    {
      case'1':  //Primer producto
      {
          lcd.print("Producto elegido");
          lcd.setCursor(0,1);
          lcd.print("chocolatina");
          lcd.setCursor(0,0);
          delay(5000);
          lcd.clear();
          pin=13;
          Motores(pin);
          Agradecer();
          if (monedas>5) 
          {
           Darcambio(monedas);
           Cambiar(vueltas);  
          }
          if(choco<=0)
          {
            lcd.print("Agotado");
            lcd.setCursor(0,1);
            lcd.print("Lo sentimos");
            lcd.setCursor(0,0);
            delay(3000);
            lcd.clear();
            Cinco();
            Serial.print("\t ¡Reponer chocolatinas!");
            choco=1;
          }
          choco--;
          num=1;
          //Registro para la empresa(Te informa del exito del producto y los restantes)
          Registro(choco, num);
          monedas=0;
          break;
      }
     case '2': //Segundo producto
      {
          lcd.clear(); 
          lcd.print("Producto elegido");
          lcd.setCursor(0,1);
          lcd.print("refresco");
          lcd.setCursor(2,0);
          delay(5000);
          lcd.clear();
          pin=12;
          Motores(pin);
          Agradecer();
          if (monedas>5) 
           {
               Darcambio(monedas);
               Cambiar(vueltas);
           }
          if(latas<=0)
          {
            lcd.print("Agotado");
            lcd.setCursor(0,1);
            lcd.print("Lo sentimos");
            lcd.setCursor(0,0);
            delay(3000);
            lcd.clear();
            Cinco();
            Serial.print("\t ¡Reponer latas!");
            latas=1;
          }
          latas--;
          num=2;
          //Registro para la empresa
          Registro(latas, num);
          monedas=0;
          break;
          }
        case '3': //Producto que no esta disponible 
         {
          lcd.print("Producto no");
          lcd.setCursor(0,1);
          lcd.print("disponible");
          lcd.setCursor(0,0);
          delay(4000);
          lcd.clear();
          Agotado(monedas);
          monedas=0;
          break;
         }
        case '4': //Producto que no esta disponible
         {
          lcd.print("Compra");
          lcd.setCursor(0,1);
          lcd.print("cancelada");
          lcd.setCursor(0,0);
          delay(3000);
          lcd.clear();
          Agotado(monedas);
          monedas=0;
          break;
      }
    }
  }
  void Agotado(int monedas)
  {
    digitalWrite(3,HIGH);
    delay(monedas*1000);
    digitalWrite(3,LOW);
  }
  void Cambiar(int vueltas)
  {
    digitalWrite(3,HIGH);
    delay(vueltas*1000);
    digitalWrite(3,LOW);
  }
  void Cinco()
  {
    digitalWrite(3,HIGH);
    delay(5000);
    digitalWrite(3,LOW);
  }
  void Agradecer()
  {
    lcd.clear();
    lcd.print("Gracias!!!");
    lcd.setCursor(3,0);
    delay(3000);
    lcd.clear();
  }
  void Darcambio(int monedas)
  {
    vueltas=monedas-5;
    lcd.print("Recoja cambio");
    lcd.setCursor(0,1);
    lcd.print(vueltas);
    lcd.setCursor(0,0);
    delay(2000);
    lcd.clear();  
  }
  void Registro(int producto, int num)
  {
    Serial.print("/Quedan ");
    Serial.print(producto);
    Serial.print(" de producto numero ");
    Serial.print(num);
    Serial.print("\n");
  }
  void Motores(int pin)
  {
    digitalWrite(pin, HIGH);
    delay(3000);
    digitalWrite(pin, LOW);
  }
