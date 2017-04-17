struct data {
  int btnPin;
  int ledPin;
  int internalState;
  boolean ledState;
};

struct data red = {.btnPin = 4, .ledPin = 12};
struct data green = {.btnPin = 2, .ledPin = 9};

void setup() {
  Serial.begin(9600);
  pinMode(red.btnPin, INPUT);
  pinMode(green.btnPin, INPUT);
  pinMode(red.ledPin, OUTPUT);
  pinMode(green.ledPin, OUTPUT);
  Serial.println("START");
}

void loop() {
  controlButton(&red);
  controlButton(&green);
  delay(10);
}

bool controlButton(struct data *data) {
  int newState = digitalRead(data->btnPin);
  bool result = false;
  if (newState == 1) {
    if (data->internalState == 0) {
      result = true;
      data->ledState = !data->ledState;
      digitalWrite(data->ledPin, data->ledState ? HIGH : LOW);
    }
  }
  data->internalState = newState;
  return result;
}



