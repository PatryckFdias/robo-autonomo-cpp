// ========== robo seguidor de linha com desvio ==========
 
// motores
#define MOTOR_ESQ_FRENTE 9
#define MOTOR_ESQ_TRAS  8
#define MOTOR_DIR_FRENTE 7
#define MOTOR_DIR_TRAS  4
#define ENABLE_A 5
#define ENABLE_B 6
 
// sensores de linha
#define SENSOR_LINHA_ESQ 2
#define SENSOR_LINHA_DIR 3
 
// ultrassônico
#define TRIG 13
#define ECHO 12
 
// sensor ativo alto (igual ao seu)
#define SENSOR_ATIVO_ALTO false
 
// velocidades
#define VEL_FRENTE 100
#define VEL_CURVA  90
#define VEL_DESVIO 90
 
// guarda ultimo lado visto
int ultima_direcao = 0;  // -1 = esquerda, 1 = direita, 0 = centro
 
void setup() {
  Serial.begin(115200);
 
  pinMode(MOTOR_ESQ_FRENTE, OUTPUT);
  pinMode(MOTOR_ESQ_TRAS, OUTPUT);
  pinMode(MOTOR_DIR_FRENTE, OUTPUT);
  pinMode(MOTOR_DIR_TRAS, OUTPUT);
  pinMode(ENABLE_A, OUTPUT);
  pinMode(ENABLE_B, OUTPUT);
 
  pinMode(SENSOR_LINHA_ESQ, INPUT);
  pinMode(SENSOR_LINHA_DIR, INPUT);
 
  // ultrassônico
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
 
  parar_motores();
  delay(2000);
}
 
void loop() {
 
  // ================== 1) VERIFICA OBSTÁCULO ==================
  long dist = medir_distancia();
  if(dist > 0 && dist < 15){      // obstáculo detectado
    desviar_obstaculo();
    return;                       // depois volta ao loop normal
  }
 
  // ================== 2) SEGUIR LINHA ==================
  bool se = ler_sensor(SENSOR_LINHA_ESQ);
  bool sd = ler_sensor(SENSOR_LINHA_DIR);
 
  if (se && sd) {
    mover_frente(VEL_FRENTE);
    ultima_direcao = 0;
  }
  else if (se && !sd) {
    virar_esquerda();
    ultima_direcao = -1;
  }
  else if (!se && sd) {
    virar_direita();
    ultima_direcao = 1;
  }
  else {
    if (ultima_direcao == -1) virar_esquerda();
    else if (ultima_direcao == 1) virar_direita();
    else mover_frente(VEL_FRENTE * 0.6);
  }
 
  delay(1);
}
 
// ================ FUNÇÕES ================
 
long medir_distancia(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
 
  long duracao = pulseIn(ECHO, HIGH, 20000);
  long cm = duracao * 0.034 / 2;
  return cm;
}
 
void desviar_obstaculo() {
 
  // 1) vira para a direita por 600ms
  digitalWrite(MOTOR_ESQ_FRENTE, HIGH);
  digitalWrite(MOTOR_ESQ_TRAS, LOW);
  analogWrite(ENABLE_A, VEL_DESVIO);
 
  digitalWrite(MOTOR_DIR_FRENTE, LOW);
  digitalWrite(MOTOR_DIR_TRAS, HIGH);
  analogWrite(ENABLE_B, VEL_DESVIO);
 
  delay(600);
 
  // 2) anda pra frente desviando
  mover_frente(VEL_DESVIO);
  delay(800);
 
  // 3) volta para a esquerda (para retornar ao caminho)
  digitalWrite(MOTOR_ESQ_FRENTE, LOW);
  digitalWrite(MOTOR_ESQ_TRAS, HIGH);
  analogWrite(ENABLE_A, VEL_DESVIO);
 
  digitalWrite(MOTOR_DIR_FRENTE, HIGH);
  digitalWrite(MOTOR_DIR_TRAS, LOW);
  analogWrite(ENABLE_B, VEL_DESVIO);
 
  delay(600);
 
  // 4) anda um pouco para tentar reencontrar a linha
  mover_frente(VEL_DESVIO * 0.9);
  delay(600);
}
 
bool ler_sensor(int pino) {
  int v = digitalRead(pino);
  return SENSOR_ATIVO_ALTO ? (v == HIGH) : (v == LOW);
}
 
void mover_frente(int vel) {
  digitalWrite(MOTOR_ESQ_FRENTE, HIGH);
  digitalWrite(MOTOR_ESQ_TRAS, LOW);
  analogWrite(ENABLE_A, vel);
 
  digitalWrite(MOTOR_DIR_FRENTE, HIGH);
  digitalWrite(MOTOR_DIR_TRAS, LOW);
  analogWrite(ENABLE_B, vel);
}
 
void virar_esquerda() {
  digitalWrite(MOTOR_ESQ_FRENTE, LOW);
  digitalWrite(MOTOR_ESQ_TRAS, LOW);
  analogWrite(ENABLE_A, 0);
 
  digitalWrite(MOTOR_DIR_FRENTE, HIGH);
  digitalWrite(MOTOR_DIR_TRAS, LOW);
  analogWrite(ENABLE_B, VEL_CURVA);
}
 
void virar_direita() {
  digitalWrite(MOTOR_ESQ_FRENTE, HIGH);
  digitalWrite(MOTOR_ESQ_TRAS, LOW);
  analogWrite(ENABLE_A, VEL_CURVA);
 
  digitalWrite(MOTOR_DIR_FRENTE, LOW);
  digitalWrite(MOTOR_DIR_TRAS, LOW);
  analogWrite(ENABLE_B, 0);
}
 
void parar_motores() {
  digitalWrite(MOTOR_ESQ_FRENTE, LOW);
  digitalWrite(MOTOR_ESQ_TRAS, LOW);
  digitalWrite(MOTOR_DIR_FRENTE, LOW);
  digitalWrite(MOTOR_DIR_TRAS, LOW);
  analogWrite(ENABLE_A, 0);
  analogWrite(ENABLE_B, 0);
}
