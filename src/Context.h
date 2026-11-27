#ifndef __CONTEXT__
#define __CONTEXT__

enum RadarState {
    IDLE,
    WORKING,
    PRE_ALARM,
    ALARM
};

enum ControlSweep {
    RSU,
    WAITING,
    RIGHT,
    LEFT
};

class Context {

public:
    // Metodo statico globale per accedere all'unica istanza
    static Context& getInstance() {
        static Context instance; // Creata una sola volta
        return instance;
    }

    // Eliminazione di copia e assegnazione per blindare il Singleton
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    RadarState getState();

    int getCurrentSector();

    ControlSweep getControlSweep();

    bool getSleepFlag();

    void setIdle();
    void setWorking();
    void setPreAlarm();
    void setAlarm();

    void setCurrentSector(int currentSector);

    void setRSU();
    void setWaiting();
    void setRight();
    void setLeft();

    void setSleepFlag(bool flag);

private:
    // Costruttore reso privato per impedire il "new Context()" esterno
    Context();
    
    // Distruttore privato (opzionale, ma coerente per un singleton che non deve essere cancellato con delete)
    ~Context() = default;

    RadarState radarState;

    int currentSector;
    
    ControlSweep controlSweep;

    bool sleepFlag;
};

#endif