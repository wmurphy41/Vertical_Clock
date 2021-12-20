const int transistor1 = A1 ;
const int transistor2 = A2 ;

void setup()
{
  pinMode (transistor1, OUTPUT);
  pinMode (transistor2, OUTPUT);
}

void loop()
{
  digitalWrite (transistor1, HIGH);
  digitalWrite (transistor2, LOW);
  delay(1000);
  digitalWrite (transistor1, LOW);
  digitalWrite (transistor2, HIGH);
  delay(1000);
}
