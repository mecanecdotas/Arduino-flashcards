// DATOS PARA CORRER EL PROGRAMA -NO CAMBIARLOS-

  #include <Wire.h>  // Librería para comunicación I2C
  #include <LiquidCrystal_I2C.h>  // Librería para el control de LCD I2C

  LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C del módulo LCD y tamaño del LCD (16 columnas x 2 filas)

  const int dtxt = 2600; //delay para el texto


// Definir los pines de los botones para Sí y No
const int pinSiButton = 2;
const int pinNoButton = 3;

// Definir cuántas preguntas hay
const int preguntas = 12;
// Definir el contenido de cada pregunta [Cada pregunta debe tener 16 caracteres máximo si se usa la LCD de 16x2]
const char *Preguntas[preguntas] = {"sech= -sech*tanh", "cot-1=-1/(1+x^2)", "b^x = b^x*ln(b)", 
"csc-1=-1/(1+x^2)", "cot = -csc^2", "csc = -csc*cot", "tan = cos", 
"cos = -sen", "logax = 1/(xlna)", "lnx= 1/(x)", "lnu= 1/(x)", "logau= u'/(ulna)"};

bool respuestasPreguntas[preguntas];  // Almacena las respuestas del usuario

// Definir las respuestas correctas para cada pregunta
const bool respuestasCorrectas[preguntas] = {
  true, true, true, false, true, true, false, true, true, true, false, true 
  // Asignar false si la respuesta es incorrecta y true si es correcta
};

bool preguntadas[preguntas]; // Verifica si una pregunta ya fue hecha


  int correctas = 0; // Contador de respuestas correctas
  int preguntasHechas = 0;

// DATOS PARA CORRER LA PANTALLA -NO CAMBIARLOS-
void setup() {
  Serial.begin(9600);

  pinMode(pinSiButton, INPUT);
  pinMode(pinNoButton, INPUT);

  lcd.init();  // Inicializar el LCD
  lcd.backlight();  // Encender el backlight del LCD
  lcd.clear(); // Limpiar el LCD en caso tenga algo escrito

  // MENSAJE MOTIVADOR DE INTRO
  lcd.clear();
  lcd.display();
  lcd.setCursor(3,0); // Asigna un valor en x, y en la pantalla en donde saldrá el texto
  lcd.print("Si no aciertas"); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
  lcd.setCursor(2,1);
  lcd.print("pierdes calculo :)"); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
  lcd.display();

  delay (dtxt);

  lcd.clear();
  lcd.display();
  lcd.setCursor(3,2);
  lcd.print("<- Si   No ->"); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
  lcd.display();

  delay (dtxt);

}

void loop() {

  // Activa la verificación de preguntas ya hechas
  for (int i = 0; i < preguntas; i++) {
   preguntadas[i] = false;
  }


  // Preguntar cada pregunta aleatoriamente y registar respuesta
  while (preguntasHechas < preguntas) {
    int x = random (0, preguntas);
    int i = x;

  // Verificar que la pregunta no ha sido hecha
    if (!preguntadas[x]) {
      preguntadas[x] = true;
      preguntasHechas++;

    // Definir el texto de inicio de cada pregunta
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("La derivada de"); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
      lcd.setCursor(0,1);
      lcd.print(Preguntas[x]);
      lcd.display();
      delay (dtxt);

    // Esperar una respuesta 
      while (true) {
        if (digitalRead(pinSiButton) == HIGH) {
          delay(100);
          respuestasPreguntas[x] = true;
          break;
        } else if (digitalRead(pinNoButton) == HIGH) {
          delay(100);
          respuestasPreguntas[x] = false;
          break;
        }
      }
    }

    // Verificar si la respuesta es correcta
    if (respuestasPreguntas[x] == respuestasCorrectas[x]) {
      correctas++;
    }

    delay (500); // Pequeña pausa para evitar múltiples lecturas 
  }

  // Mostrar cuántas respuestas correctas se tuvo
  lcd.clear();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print(correctas);
  lcd.print(" correctas"); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
  lcd.setCursor(0,1);
  lcd.print("de "); // [Este texto debe tener 16 caracteres máximo si se usa la LCD de 16x2]
  lcd.print(preguntas);
  lcd.display();

  delay(5000);  // Esperar 5 segundos antes de realizar otra ronda

}