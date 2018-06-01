int aval = 0;      // analog value

void setup() {
  Serial.begin(200000);      // set baudrate
  DIDR0 = 0x3F;            // digital inputs disabled
  ADMUX = 0x43;            // measuring on ADC3, use the internal 5V reference
  ADCSRA = 0xAB;           // AD-converter on, interrupt enabled, prescaler = 8
  ADCSRB = 0x40;           // AD channels MUX on, free running mode
  bitWrite(ADCSRA, 6, 1);  // Start the conversion by setting bit 6 (=ADSC) in ADCSRA
  sei();                   // set interrupt flag
}

void loop() {
} 

/*** Interrupt routine ADC ready ***/
ISR(ADC_vect) {
  aval = ADCL;        // store lower byte ADC
  aval += ADCH << 8;  // store higher bytes ADC
  Serial.write( 0xff );                                                         
  Serial.write( (aval >> 8) & 0xff );                                            
  Serial.write( aval & 0xff );
}
