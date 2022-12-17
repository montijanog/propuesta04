#include "mbed.h"
 
/*
   
*/
//Ejercicio propuesto, En esta versionse planteará el problema con estados secuenciales, donde: 
// 6) Que un led parpadee en función de las pulsaciones de un botón.

        //a) Sin pulsación 1s

        //b) Primera pulsación cada 0.5s  => adaptado a 4seg

        //c) Segunda pulsación cada 0.25s   

        //d) Tercera pulsación vuelvo a 1s. => adaptado a 4seg

    //Se ha modificado el tiempo de parpadeo para poder distinguir entre un estado y otro, ademas se le añade de que cuando se haga 
    // cuarta pulsacion, vuelva al origen (cada 1 seg) y empezar  un nuevo ciclo.


enum estados {Inicio, Parpadeo_1, Parpadeo_2, Parpadeo_3} estado;
 
Timer timer;
Timer timer_1;
Timer timer_2;
Timer timer_3;

 
 
DigitalOut led1(D2);
DigitalIn boton(D3);
 
void estadoInicio()
{
    if(boton==1 ) {
        timer.reset();
        timer.stop();
        timer_1.start();
        //led1=0;
        estado=Parpadeo_1;
    }

    
    else if(timer.read()>1.0f  && boton==0){

        led1 = !led1;
        timer.reset();
                
    }
}  
    
 
void estadoParpadeo_1(){
    
    if(boton==1  ) {
        timer_1.reset();
        timer_1.stop();
        timer_2.start();
        //led1=0;
        estado=Parpadeo_2;
        
    }
    else if(timer_1.read()>3.0f   && boton==0 ){

        led1 = !led1;

        timer_1.reset();

    }

    
}

void estadoParpadeo_2(){
    if(boton==1 ) {
        timer_2.reset();
        timer_2.stop();
        timer_3.start();
        //led1=0;
        estado=Parpadeo_3;
    }
    else if(timer_2.read()>0.25f   && boton==0){

        led1 = !led1;

        timer_2.reset();

    }

    
}

void estadoParpadeo_3(){
    if(boton==1 ) {
        timer_3.reset();
        timer_3.stop();
        
        timer.start();
        //led1=0;
        estado=Inicio;
    }
    
    else if(timer_3.read()>5.0f  && boton==0){

        led1 = !led1;
        
        timer_3.reset();

    }

    
}



int main(){
    led1=0;
    estado=Inicio;
    timer.reset();
    timer.start();
    //timer_1.start();
    //timer_2.start();
    //timer_3.start();


    while(1) {
        switch(estado) {
            case Inicio:
                estadoInicio();
                break;
            case Parpadeo_1:
                estadoParpadeo_1();
                break;
            case Parpadeo_2:
                estadoParpadeo_2();
                break;
            case Parpadeo_3:
                estadoParpadeo_3();
                break;
        }
 
    }
}

