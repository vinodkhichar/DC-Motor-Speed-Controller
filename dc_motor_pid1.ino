// Programa para controle de Motores Utilizando Algoritimo PID
// Set Point Alteravel através de potênciometro

// Mapeamento Hardware
#define PWM_OUT       3
#define ENCODER_A 2
#define POT_IN A0

// Variaveis Globais

int output;           // define a saída de pwm
int speed;        // velocidade do motor
int lastError = 0;    // declara o ultimo erro

int setpoint;
int error = 0;           // erro atual
int I_error = 0;         // ganho integral
int D_error = 0;         // ganho derivativo
float KP = 0.1;          // constante proporcional
float KI = 0.0001;       // constante integrativa
float KD = 0.001;        // constante derivativa


void setup() {
  
  Serial.begin(9600);                 // inicia a comunicação serial
  
  pinMode(ENCODER_A, INPUT);         // define o encoder para enviar dados
  pinMode(POT_IN, INPUT);     // define o potenciometro para enviar dados e controlar o valor de set point
  pinMode(PWM_OUT, OUTPUT);          // define a porta 3 para envio de sinal PWM para controle de velocidade
  
  output = 10;                    // define um valor inicial para pwm_valor 
  analogWrite(PWM_OUT, output);   // controla o valor pwm através da saida porta 3
  }

void loop() {
   // calcula o valor de set point apartir da leitura analógica do potenciometro
  setpoint = map(analogRead(POT_IN), 0,1023,0,600);  
   
  // realiza a leitura do encoder e transforma o valor dos pulsos em velocidade
  speed = 19.1*((60*1000*10) / pulseIn(ENCODER_A, HIGH)); 
  
  error = setpoint - speed; // calcula o valor do erro
   
  I_error += error; // somatorio do erro
  D_error = lastError - error; // variação do erro
  // como esse loop vai ser chamado regularmente, podemos 
  // supor que dt é constante e não incluilo nas contas acima.
  // dt está junto de KP, KI, KD, de forma implicita.
  
  // Implementação do Algorítimo PID
  output += KP*error + KI*I_error + KD*D_error;     
  
  // limita a saida do controle para os valores vãlidos de pwm (10-255)
  output = constrain(output, 10, 255);
 
  // envia o sinal para o "motor"
  analogWrite(PWM_OUT, output);
  
  // imprime os valores de speed e setpoint.
  // valores em RPM
  // utilize a função de gráficos do monitor serial!  
  Serial.print(speed);     
  Serial.print(",");
  Serial.println(setpoint);  
}
