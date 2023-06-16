//Carro
float v_inst    = 0;
float v_passada = 0;

//Filtro
float v_filtro       = 00;
float v_filtrada     = 0;
float v_filtrada_pas = 0;

//Controlador
double p_value  = 0;
double i_value  = 0;
double u        = 0;
double erro     = 0;

//Amostragem
unsigned long previousMillis = 0; 
const    long period = 50;

//Array
int v_array[] = { 100, 110, 100, 90 };

int array_selector = 0;
int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("Value1, Value2"); //, Value3");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= period) {
    previousMillis = currentMillis;  
    counter++;
    
    //Entrada
    //v_inst = ( v_passada * 0.9753 ) + ( v_array[array_selector] * 0.02469 ) + random(-1,1) * 0.05;
    v_inst = ( v_passada * 0.9753 ) + ( u * 0.02469 ) + random(-1,1) * 0.05;
    v_passada = v_inst;

    //Filtro
    v_filtro = 0.9691* v_filtrada_pas + 0.01547*(v_inst + v_filtrada);
    v_filtrada_pas = v_filtro;
    v_filtrada = v_inst;

    //Controlador PI
    erro = v_array[array_selector] - v_filtro;

    double kp_const = 2.5; 
    double ki_const = 0.9; 
    
    p_value  = (erro * kp_const);
    i_value  = (i_value + (erro * ki_const) * 0.05);
    
    u = p_value + i_value;

    //Serial.print(v_inst);
    //Serial.print(",");
    //Serial.println(v_filtro);

    Serial.print(v_array[array_selector]);
    Serial.print(",");
    Serial.println(v_filtro);

    //Serial.print(",");
    //Serial.println(u);

    //Controle do array
    if (counter == 300 ) {
      counter = 0;

      array_selector++;

      if (array_selector == 4){
        array_selector = 0;
      }
    }
  }
}
