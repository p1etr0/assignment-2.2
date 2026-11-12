#ifndef __POT__
#define __POT__

class Potentiometer {
 
public: 
  Potentiometer(int pin);
  
  float getValue();

  // ci serve sapere il tempo l'ultima lettura?
  // forse per debounce?
  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;
  int pin;
  float value;
};

#endif