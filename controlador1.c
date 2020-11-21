/*
 * File:          controlador1.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <webots/supervisor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define QtddSensoresProx 8
#define QtddLeds 10
#define dife 0.01

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  
  int i=0;
  char texto[256];
  double LeituraSensorProx[QtddSensoresProx];
  double AceleradorDireito=1.0, AceleradorEsquerdo=1.0;
  const double *posicao; //variáel que vai receber a posição do robo
  
  double x[250]; // vetor que armazena a posição do X quando ocorre colisão
  double z[250]; // vetor que armazena a posição do Z quando ocorre colisão
  int j = 0;  // variável que controla o armazenamento nos vetores x[j] e z[j] (while)
  int c = 0;  // contador para aumentar o tempo de colisão
  int qtdLed = 0;  //flag para piscar leds
  int acLed = 0;   //ascende led com colisão da caixa que se mexe
  double testeP; //variavel que faz o teste para valores positivos
  double testeN; //variavel que faz o teste para valores negativos
  
  
  /* necessary to initialize webots stuff */
  
  for(i=0;i<257;i++) texto[i]='0';
  
  wb_robot_init();
  
  //configurei MOTORES
  WbDeviceTag MotorEsquerdo, MotorDireito;
  
  MotorEsquerdo = wb_robot_get_device("left wheel motor");
  MotorDireito = wb_robot_get_device("right wheel motor");
  
  wb_motor_set_position(MotorEsquerdo, INFINITY);
  wb_motor_set_position(MotorDireito, INFINITY);
  
  wb_motor_set_velocity(MotorEsquerdo,0);
  wb_motor_set_velocity(MotorDireito,0);
  
  
   //configurei Sensores de Proximidade
   WbDeviceTag SensorProx[QtddSensoresProx];
   
   SensorProx[0] = wb_robot_get_device("ps0");
   SensorProx[1] = wb_robot_get_device("ps1");
   SensorProx[2] = wb_robot_get_device("ps2");
   SensorProx[3] = wb_robot_get_device("ps3");
   SensorProx[4] = wb_robot_get_device("ps4");
   SensorProx[5] = wb_robot_get_device("ps5");
   SensorProx[6] = wb_robot_get_device("ps6");
   SensorProx[7] = wb_robot_get_device("ps7");
   
   wb_distance_sensor_enable(SensorProx[0],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[1],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[2],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[3],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[4],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[5],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[6],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[7],TIME_STEP);
 
  
   WbNodeRef robot_node = wb_supervisor_node_get_from_def("meu_robo"); //captura o supervisor
   WbFieldRef trans_field = wb_supervisor_node_get_field(robot_node, "translation"); //identifica o campo de posição
   
    //config leds
    WbDeviceTag Leds[QtddLeds];
    Leds[0] = wb_robot_get_device("led0");
    Leds[1] = wb_robot_get_device("led1");
    Leds[2] = wb_robot_get_device("led2");
    Leds[3] = wb_robot_get_device("led3");
    Leds[4] = wb_robot_get_device("led4");
    Leds[5] = wb_robot_get_device("led5");
    Leds[6] = wb_robot_get_device("led6");
    Leds[7] = wb_robot_get_device("led7");
    Leds[8] = wb_robot_get_device("led8");
    Leds[9] = wb_robot_get_device("led9");
  
  
  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   
   
   
   
  while (wb_robot_step(TIME_STEP) != -1) {
    for(i=0;i<256;i++) texto[i]=0;
    //memcpy(texto,0,10);
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */
    for(i=0;i<QtddSensoresProx;i++){
       LeituraSensorProx[i]= wb_distance_sensor_get_value(SensorProx[i])-60;
       sprintf(texto,"%s|%d: %5.2f  ",texto,i,LeituraSensorProx[i]);
       posicao = wb_supervisor_field_get_sf_vec3f(trans_field);

    }
    printf("%s\n",texto);
    printf("Posicao do robo: x= %f   y= %f z= %f\n", posicao[0], posicao[1], posicao[2]);
    // faz o led piscar
    //wb_led_set(Leds[0], wb_led_get(Leds[0])*-1);
    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
    
   
    
    
    
    
    //=========== sensores ================//
    
    
    if(LeituraSensorProx[0]>350){
      AceleradorDireito = 1;
      AceleradorEsquerdo = 1;
      
      x[j] = posicao[0]; // preenche o vetor x[]
      z[j] = posicao[2]; // preenche o vetor z[] 
      printf("COLISÃO EM x%d %f | z%d %f\n", j,  x[j], j, z[j]); //mostra o valor de x e z na hora da colisão
      
      
      if(c > 7){  // if funciona como contador para o a colisão demorar mais tempo
        AceleradorDireito = -1;
        AceleradorEsquerdo = 1;
        
        
        //se X maior que 0 a conta do deslocamento do objeto será feita aqui 
        if(x[0] > 0){
          if(x[2] > x[8]){
            testeP = x[2] - x[8]; // calcula a distância entre x[2] e x[8]
            
            if(testeP > 0.015){ // se distância maior que 0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S0 <=================\n");
               qtdLed = qtdLed + 1;
            }
          }
          
          else{
            testeP = x[8] - x[2]; // calcula a distância entre x[2] e x[8]
            if(testeP > 0.015){ // se distância maior que 0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S0 <=================\n");
              qtdLed = qtdLed + 1;
            }
          }  
        }
        
        
        //se X menor que 0 a conta do deslocamento do objeto será feita aqui
        else if(x[0] < 0){ 
          if(x[2] > x[8]){
            testeN = (x[8]) - (x[2]);  // calcula a distância entre x[2] e x[8]
            
            if(testeN < -0.015){ // se distância menor (mais negativa) que -0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S0 <=================\n");
               qtdLed = qtdLed + 1;
            }
          }
          
          
          else{
            testeN = (x[2]) - (x[8]);  // calcula a distância entre x[2] e x[8]
            if(testeN < -0.015){ // se distância menor (mais negativa) que -0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S0 <=================\n");
               qtdLed = qtdLed + 1;
            }
          }  
        }
      }
      j++;
      c++;      
     }
     
     
     else if(LeituraSensorProx[7]>350) {
      AceleradorDireito = 1;
      AceleradorEsquerdo = 1;
     
      x[j] = posicao[0]; // preenche o vetor x[]
      z[j] = posicao[2]; // preenche o vetor z[]
      printf("COLISÃO EM x%d %f | z%d %f\n", j,  x[j], j, z[j]); //mostra o valor de x e z na hora da colisão
      
     if(c > 7){  // if funciona como contador para o a colisão demorar mais tempo
        AceleradorDireito = -1;
        AceleradorEsquerdo = 1;

        
        //se X maior que 0 a conta do deslocamento do objeto será feita aqui 
        if(x[0] > 0){
          if(x[2] > x[8]){
            testeP = x[2] - x[8]; // calcula a distância entre x[2] e x[8]
            
            if(testeP > 0.015){ // se distância maior que 0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S7 <=================\n");
               qtdLed = qtdLed + 1;
            }
          }
          
          else{
            testeP = x[8] - x[2];  // calcula a distância entre x[2] e x[8]
            if(testeP > 0.015){ // se distância maior que 0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S7 <=================\n");
               qtdLed = qtdLed + 1;
            }
          }  
        }
        
        //se X menor que 0 a conta do deslocamento do objeto será feita aqui
        else if(x[0] < 0){ 
          if(x[2] > x[8]){
            testeN = (x[8]) - (x[2]); // calcula a distância entre x[2] e x[8]
            
            if(testeN < -0.015){ // se distância menor (mais negativa) que -0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S7 <=================\n");
               qtdLed = qtdLed + 1;
            } 
          }
          
          else{
            testeN = (x[2]) - (x[8]); // calcula a distância entre x[2] e x[8]
            if(testeN < -0.015){ // se distância menor (mais negativa) que -0.015 logo o objeto mexeu
              printf("=================> OBJETO MÓVEL DETECTADO PELO SENSOR S7 <=================\n");
              qtdLed = qtdLed + 1;
            }
          }
        }
      }
      
      
      
      j++;
      c++;
     }
      
      
      
      //aciona sensores/motores quando ocorre valores maiores do que foi definido.
     else if(LeituraSensorProx[1]>500) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
     else if(LeituraSensorProx[2]>1000) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
     else if(LeituraSensorProx[3]>1000) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
     else if(LeituraSensorProx[4]>1000) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
     else if(LeituraSensorProx[5]>1000) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
     else if(LeituraSensorProx[6]>500) {
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;
     }
     
      
     else {  // faz o robo andar reto se nenhum sensor é acionado
      AceleradorDireito = 1;
      AceleradorEsquerdo = 1;
      j=0;
      c=0;
     }
      
   
     if(qtdLed > 2){ // if para ativar a led pelo contador 
      
     
       wb_led_set(Leds[0], 0);
       wb_led_set(Leds[1], 0);
       wb_led_set(Leds[2], 0);
       wb_led_set(Leds[3], 0);
       wb_led_set(Leds[4], 0);
       wb_led_set(Leds[5], 0);
       wb_led_set(Leds[6], 0);
       wb_led_set(Leds[7], 0);
     
     for(int jk = 0; jk <= 6; jk++){  //piscar led 3 vezes
         
       wb_led_set(Leds[0], 1);
       wb_led_set(Leds[1], 1);
       wb_led_set(Leds[2], 1);
       wb_led_set(Leds[3], 1);
       wb_led_set(Leds[4], 1);
       wb_led_set(Leds[5], 1);
       wb_led_set(Leds[6], 1);
       wb_led_set(Leds[7], 1);
       wb_led_set(Leds[0], 0);
       wb_led_set(Leds[1], 0);
       wb_led_set(Leds[2], 0);
       wb_led_set(Leds[3], 0);
       wb_led_set(Leds[4], 0);
       wb_led_set(Leds[5], 0);
       wb_led_set(Leds[6], 0);
       wb_led_set(Leds[7], 0);
       
     }
   
   
     if(acLed == 0){	//acende 1 led
          wb_led_set(Leds[0], 1);    
     }
     
     if(acLed == 1){	//acende 2 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);  
     }
     
     if(acLed == 2){	//acende 3 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);       
     }
     
     if(acLed == 3){	//acende 3 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);    
     }
     
     if(acLed == 4){	//acende 4 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
     }
     
     if(acLed == 5){	//acende 5 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
          wb_led_set(Leds[5], 1);
     }
     
     if(acLed == 6){	//acende 6 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
          wb_led_set(Leds[5], 1);
          wb_led_set(Leds[6], 1);
     }
     
     if(acLed == 7){ 	//acende 7 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
          wb_led_set(Leds[5], 1);
          wb_led_set(Leds[6], 1);
          wb_led_set(Leds[7], 1);  
     }
     
     if(acLed == 8){ 	//acende 8 leds
          wb_led_set(Leds[0], 1);
          wb_led_set(Leds[1], 1);
          wb_led_set(Leds[2], 1);
          wb_led_set(Leds[3], 1);
          wb_led_set(Leds[4], 1);
          wb_led_set(Leds[5], 1);
          wb_led_set(Leds[6], 1);
          wb_led_set(Leds[7], 1); 
     }
     acLed++;
     qtdLed = 0;
     
   }
    
    WbNodeRef robot_node = wb_supervisor_node_get_from_def("ePuck"); //captura o supervisor
    wb_motor_set_velocity(MotorEsquerdo,6*AceleradorEsquerdo);
    wb_motor_set_velocity(MotorDireito, 6*AceleradorDireito);
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}


