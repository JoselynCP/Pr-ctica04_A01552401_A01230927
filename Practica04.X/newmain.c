
////+++++++++++++++++++++++++++++++++++++| LIBRARIES / HEADERS |+++++++++++++++++++++++++++++++++++++
#include "device_config.h" // Libería de device_config.h anexada anteriormente en la otra pestaña
//+++++++++++++++++++++++++++++++++++++| DIRECTIVES |+++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 1000000 // Identificador con constante valor de 1000000
#define ONE_SECOND 1000 // Identificador con constante valor de 1000

//+++++++++++++++++++++++++++++++++++++| DATA TYPES |+++++++++++++++++++++++++++++++++++++
enum por_dir{ output, input };              // Variable con dos estados, output = 0, input = 1  
enum por_ACDC { digital, analog };          // Variable con dos estados, digital = 0, analog = 1
enum resistor_state { set_ON, res_ON };     // Variable con dos estados, set_ON = 0, res_ON = 1
enum led_state { led_OFF, led_ON };         // Variable con dos estados, led_OFF = 0, led_ON = 1
enum butto_state { pushed, no_pushed };     // Variable con dos estados, pushed = 0, no_pushed = 1

//+++++++++++++++++++++++++++++++++++++| ISRs |+++++++++++++++++++++++++++++++++++++
// ISR for high priority
void __interrupt ( high_priority ) high_isr( void ); //
// ISR for low priority
void __interrupt ( low_priority ) low_isr( void );  //

//+++++++++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void ); //Función prototipo para iniciar los puertos

//+++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++
void main( void ){
    portsInit(); //Llama a la función para iniciar los puertos
    while(1){ // Ciclo que siempre será verdadero y por tanto permanecerá ejecutándose 
        if(PORTBbits.RB4 == pushed)         // Si se presiona el botón RB4 de la placa // es decir que butto_state sea pushed=0
            LATAbits.LATA7 = led_OFF;       // Apaga el LED en RA7 // led_state, led_OFF=0
        else                                // Si no se presiona el botón 
            LATAbits.LATA7 = led_ON;        // Entonces enciende el LED en RA7 y mantenlo encendido // led_state, led_ON=1
        LATAbits.LATA4 = led_ON;            // Enciende el LED en RA4  // led_state, led_ON=1
        __delay_ms(ONE_SECOND);             // Enciéndelo durante 1000ms=1s 
        LATAbits.LATA4 = led_OFF;           // Después del tiempo transcurrido, apaga el LED en RA4 // led_state, led_OFF=0
        __delay_ms(ONE_SECOND);             // Mantenlo apagado durante 1000ms=1s
    }
}

//+++++++++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void ){
    ANSELA = digital;                       // Se declara el puerto A como digital // por_ACDC , digital=0
    TRISAbits.TRISA4 = output;              // RA4 se define como salida LED   //  por_dir, output=0
    TRISAbits.TRISA7 = output;              // RA7 se define como salida  LED //  por_dir, output=0
    ANSELB = digital;                       // Se declara el puerto B como digital // por_ACDC , digital=0
    TRISBbits.TRISB4 = input;               // RA7 se define como entrada PULSADOR // por_dir, input=1

}
//El programa mantendrá el LED RA4 prendiendo y apagando cada 1s y mantendrá encendido RA7 hasta que se pulse el botón RB4, el cuál apagará RA7 durante un ciclo mientras que RA4 habrá encendido y apagado 