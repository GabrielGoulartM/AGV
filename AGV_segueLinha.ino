int LedIr1 = 4;
int LedIr2 = 2;
int IN1 = 3;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int enable1 = 12;
int enable2 = 13;
int ir1SensorPin = 8; // Pino digital do primeiro sensor IR
int ir2SensorPin = 7; // Pino digital do segundo sensor IR

void setup() {
  // Inicia a comunicação serial para monitoramento
  Serial.begin(9600);

  // Define os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(enable1, HIGH);
  digitalWrite(enable2, HIGH);
  
  pinMode(ir1SensorPin, INPUT); // Configura o pino do primeiro sensor IR como entrada digital
  pinMode(ir2SensorPin, INPUT); // Configura o pino do segundo sensor IR como entrada digital

  //Leds para monitorar o movimento dos motores
  pinMode(LedIr1, OUTPUT);
  pinMode(LedIr2, OUTPUT);
}

void loop() {
  int ir1Value = digitalRead(ir1SensorPin); // Lê o valor do primeiro sensor IR (HIGH ou LOW)
  int ir2Value = digitalRead(ir2SensorPin); // Lê o valor do segundo sensor IR (HIGH ou LOW)

  digitalWrite(LedIr1, LOW);
  digitalWrite(LedIr2, LOW);

  // Imprime os valores dos sensores para o monitor serial
  Serial.print("Valor do Primeiro Sensor IR: ");
  Serial.println(ir1Value);
  Serial.print("Valor do Segundo Sensor IR: ");
  Serial.println(ir2Value);

  // Move para frente enquanto ambos os sensores IR detectam a linha
  while (ir1Value == LOW && ir2Value == LOW) {
    moverFrente(120); // Velocidade média para frente    
    ir1Value = digitalRead(ir1SensorPin); // Atualiza o valor do primeiro sensor IR
    ir2Value = digitalRead(ir2SensorPin); // Atualiza o valor do segundo sensor IR
  }

  // Vira à direita se apenas o ir1 detectar a linha
  if (ir1Value == HIGH && ir2Value == LOW) {
    pararMotores();
    delay(200);
    virarDireita(175);
    delay(120);
    ir1Value = digitalRead(ir1SensorPin); // Atualiza o valor do primeiro sensor IR
    ir2Value = digitalRead(ir2SensorPin); // Atualiza o valor do segundo sensor IR
  }

  // Vira à esquerda se apenas o ir2 detectar a linha
  if (ir1Value == LOW && ir2Value == HIGH) {
    pararMotores();
    delay(200);
    virarEsquerda(175);
    delay(120);
    ir1Value = digitalRead(ir1SensorPin); // Atualiza o valor do primeiro sensor IR
    ir2Value = digitalRead(ir2SensorPin); // Atualiza o valor do segundo sensor IR
  }

 
}


// Funções para movimentação do AGV
void moverFrente(int velocidade) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);
}

void virarDireita(int velocidade) {
  analogWrite(IN1, velocidade);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);
}

void virarEsquerda(int velocidade) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);
}

void pararMotores() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
