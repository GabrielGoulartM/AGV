// Posição Inicial da partícula
int ledX = 2;
int ledY = 4;
int obj = 0;
int IN1 = 3;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int enable1 = 12;
int enable2 = 13;
int ir1SensorPin = 8; // Pino digital do primeiro sensor IR
int ir2SensorPin = 7; // Pino digital do segundo sensor IR

// Funções para movimentação do AGV
void moverFrente(int velocidade) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);
}

void moverRe(int velocidade) {
  digitalWrite(IN1, velocidade);
  analogWrite(IN2, LOW);
  digitalWrite(IN3, velocidade);
  analogWrite(IN4, LOW);
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

void direitaNoventa() {
  analogWrite(IN1, 190);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, 190);

}

void esquerdaNoventa() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 190);
  analogWrite(IN3, 190);
  digitalWrite(IN4, LOW);

}




int xInicial = 0;
int yInicial = 0;

// Posição final da partícula
int xFinal = 3;
int yFinal = 2;

// Posição Cardeal Inicial: N = Norte, S = Sul, L = Leste, O = Oeste
char cardialAtual = 'S';


// Função de mover em X
void moverX() {
  // Movimentação enquanto linha inicial é diferente da linha final
  while (xInicial != xFinal) {
    digitalWrite(ledX, LOW);
    // Verifica se ambos os sensores IR estão em HIGH (passou por um nó)
    if (ambosSensoresHIGH()) {
      // Atualiza a linha inicial apenas se os sensores estiverem em HIGH
      if (xInicial < xFinal) {
        xInicial++;
      } else {
        xInicial--;
      }
      pararMotores();
      delay(1000);
      moverFrente(180);
      delay(350);
    } else {
      // Chama a função para mover para frente apenas se os sensores não estiverem em HIGH
      moverAfrenteAGV();
    }
  }
  //Led liga quando chega no ponto X designado
  digitalWrite(ledX, HIGH);
  obj = 1;
  //Hard-coded ajustar ponto final
  pararMotores();
  delay(3000);
}



// Função de mover em Y
void moverY() {
  while (yInicial != yFinal) {
    digitalWrite(ledY, LOW);
    // Verifica se ambos os sensores IR estão em HIGH (passou por um nó)
    if (ambosSensoresHIGH()) {
      // Atualiza a variavel apenas se os sensores estiverem em HIGH
      if (yInicial < yFinal) {
        yInicial++;
      } else {
        yInicial--;
      }
      pararMotores();
      delay(1000);
      moverFrente(180);
      delay(350);
    } else {
    // Chama a função de andar pra frente se os sensores nao estiverem HIGH
    moverAfrenteAGV();
    }
  }
// Liga a led quando chega no ponto Y designado
digitalWrite(ledY, HIGH);
// Hard-coded 
pararMotores();
delay(5000);
obj = 1;
}

// Função para girar 180 graus
void centoOitenta() {
    Serial.println("Girar 180 graus.");
    delay(2000);
}






// Função para verificar e ajustar a orientação da partícula
void ajustarOrientacao(char direcaoDesejada) {
  if (cardialAtual == direcaoDesejada) {
        pararMotores();
        delay(1000);
        moverFrente(180);
        delay(350);
        return;  // Sai da função ajustarOrientacao se a condição for atendida
    }
    while (cardialAtual != direcaoDesejada) {
        switch (direcaoDesejada) {
            case 'N':
                switch (cardialAtual) {
                    case 'S':
                        centoOitenta();
                        break;
                    case 'L':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        esquerdaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'O':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        direitaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                }
                break;
            case 'S':
                switch (cardialAtual) {
                    case 'N':
                        centoOitenta();
                        break;
                    case 'L':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        direitaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'O':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        esquerdaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                }
                break;
            case 'L':
                switch (cardialAtual) {
                    case 'N':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        direitaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'S':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        esquerdaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'L':
                        pararMotores();
                        delay(1000);
                        moverFrente(180);
                        delay(350);
                        break;
                }
                break;
            case 'O':
                switch (cardialAtual) {
                    case 'N':
                         pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        esquerdaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'S':
                        pararMotores();
                        delay(1000);
                        moverFrente(120);
                        delay(300);
                        pararMotores();
                        delay(1000);
                        esquerdaNoventa();
                        delay(700);
                        pararMotores();
                        moverFrente(150);
                        delay(500);
                        break;
                    case 'L':
                        centoOitenta();
                        break;
                }
                break;
        }

        // Atualiza o valor de cardialAtual após a movimentação
        cardialAtual = direcaoDesejada;
       
    }
}



void moverAfrenteAGV() {
  int ir1Value = digitalRead(ir1SensorPin);
  int ir2Value = digitalRead(ir2SensorPin);


  Serial.print("Valor do Primeiro Sensor IR: ");
  Serial.println(ir1Value);
  Serial.print("Valor do Segundo Sensor IR: ");
  Serial.println(ir2Value);

  while (ir1Value == LOW && ir2Value == LOW) {
    moverFrente(122);
    ir1Value = digitalRead(ir1SensorPin);
    ir2Value = digitalRead(ir2SensorPin);
  }

  if (ir1Value == HIGH && ir2Value == LOW) {
    pararMotores();
    delay(200);
    virarDireita(150);
    delay(120);
    ir1Value = digitalRead(ir1SensorPin);
    ir2Value = digitalRead(ir2SensorPin);
  }

  if (ir1Value == LOW && ir2Value == HIGH) {
    pararMotores();
    delay(200);
    virarEsquerda(150);
    delay(120);
     ir1Value = digitalRead(ir1SensorPin);
    ir2Value = digitalRead(ir2SensorPin);
  }
}


bool ambosSensoresHIGH() {
  return digitalRead(ir1SensorPin) == HIGH && digitalRead(ir2SensorPin) == HIGH;
}


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
  pinMode(ledX, OUTPUT);
  pinMode(ledY, OUTPUT);

}


void tomarDecisaoX() {
  while (xInicial != xFinal) {
    char direcaoX = (xInicial > xFinal) ? 'O' : 'L';
    ajustarOrientacao(direcaoX);
    delay(100);
    moverX();
  }
}

void tomarDecisaoY() {
  while (yInicial != yFinal) {
    char direcaoY = (yInicial > yFinal) ? 'N' : 'S';
    ajustarOrientacao(direcaoY);
    delay(100);
    moverY();
  }
}



void loop() {

moverAfrenteAGV();

    
// Movimenta o AGV para frente até que ambos os sensores detectem HIGH
  while (!ambosSensoresHIGH()) {
    moverAfrenteAGV();
  }
  // Ativa o trecho de código quando ambos os sensores estão em HIGH

if (obj == 0) {
  tomarDecisaoX();
}
 
if (obj == 1) {
  delay(1000);
  moverRe(120);
  delay(300);
  tomarDecisaoY();
}

 

}