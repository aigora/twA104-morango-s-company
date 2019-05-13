#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
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
byte choco, latas;

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
  /*
   * La funcion malloc se emplearia para que el dueño de la maquina eligiese la cantidad de productos ofertados,  
   * en nuestro caso debido a las limitaciones de hardware, no podemos emplearla, debido a la falta de pines disponibles 
   * de Arduino.
  */
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
                digitalWrite(3,HIGH);
                delay(monedas);
                digitalWrite(3,LOW);
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
    } while (tecla <'1' || tecla >'4'); //Esta linea habria que modificarla para la funcion malloc,al igual que las opciones del teclado matricial y añadir lso nuevos casos
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
          digitalWrite(13,HIGH);
          delay(3000);
          digitalWrite(13,LOW);
          lcd.clear();
          lcd.print("Gracias!!!");
          lcd.setCursor(0,3);
          delay(3000);
          lcd.clear();
          if (monedas>5) 
          {
           vueltas=monedas-5;
           lcd.print("Recoja cambio");
           lcd.setCursor(0,1);
           lcd.print(vueltas);
           lcd.setCursor(0,0);
           delay(2000);
           lcd.clear();
           digitalWrite(3,HIGH);
           delay(vueltas*1000);
           digitalWrite(3,LOW);
          }
          if(choco<=0)
          {
            lcd.print("Agotado");
            lcd.setCursor(0,1);
            lcd.print("Lo sentimos");
            lcd.setCursor(0,0);
            delay(3000);
            lcd.clear();
            digitalWrite(3,HIGH);
            delay(5000);
            digitalWrite(3,LOW);
            Serial.print("\t ¡Reponer chocolatinas!");
            choco=1;
          }
          choco--;
          //Registro para la empresa(Te informa del exito del producto y los restantes)
          Serial.print("/");
          Serial.print(choco);
          Serial.print(" chocolatinas restantes\n");
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
          digitalWrite(12, HIGH);
          delay(3000);
          digitalWrite(12, LOW);
          lcd.clear();
          lcd.print("Gracias!!!");
          lcd.setCursor(3,0);
          delay(3000);
          lcd.clear();
          if (monedas>5) 
           {
               vueltas=monedas-5;
               lcd.print("Recoja cambio");
               lcd.setCursor(0,1);
               lcd.print(vueltas);
               delay(2000);
               lcd.clear();
               lcd.setCursor(0,0);
               digitalWrite(3,HIGH);
               delay(vueltas*1000);
               digitalWrite(3,LOW);
           }
          if(latas<=0)
          {
            lcd.print("Agotado");
            lcd.setCursor(0,1);
            lcd.print("Lo sentimos");
            lcd.setCursor(0,0);
            delay(3000);
            lcd.clear();
            digitalWrite(3,HIGH);
            delay(5000);
            digitalWrite(3,LOW);
            Serial.print("\t ¡Reponer latas!");
            latas=1;
          }
          latas--;
          //Registro para la empresa
          Serial.print("/");
          Serial.print(latas);
          Serial.print(" refrescos restantes\n");
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
          digitalWrite(3,HIGH);
          delay(monedas*1000);
          digitalWrite(3,LOW);
          monedas=0;
          break;
         }
        case '4': //Producto que no esta disponible
         {
          lcd.print("Producto no");
          lcd.setCursor(0,1);
          lcd.print("disponible");
          lcd.setCursor(0,0);
          delay(3000);
          lcd.clear();
          digitalWrite(3,HIGH);
          delay(monedas*1000);
          digitalWrite(3,LOW);
          monedas=0;
          break;
      }
    }
  }
