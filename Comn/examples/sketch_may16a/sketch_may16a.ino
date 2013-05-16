#include <Comn.h>

Comn a;

void setup()
{
  a.init("APC220", 9600);
}

void loop()
{
  a.send("78910000764");
  delay(1000);
}
