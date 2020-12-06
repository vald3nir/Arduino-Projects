// MOSI - pin 11
// MISO - pin 12
// CLK - pin 13
// CS - pin 4

#include <SPI.h>
#include <SD.h>

#define CHIP_SELECT 4

File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  while (!Serial)
  {
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(CHIP_SELECT))
  {
    Serial.println("initialization failed!");

    while (1)
    {
    }
  }

  Serial.println("initialization done.");
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile)
  {

    myFile.seek(EOF);
    myFile.println("Appended to the EOF");

    Serial.print("Writing to test.txt...");
    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");

    for (int i = 0; i < 20; i++)
    {
      myFile.println(i);
    }

    myFile.close();
    Serial.println("done.");
  }
  else
  {
    Serial.println("error opening test.txt");
  }
}

void loop()
{
}
