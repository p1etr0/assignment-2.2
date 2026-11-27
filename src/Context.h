#ifndef __CONTEXT__
#define __CONTEXT__

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

    bool isIdle();
    bool isWorking();
    bool isPreAlarm();
    bool isAlarm();

    void setIdle();
    void setWorking();
    void setPreAlarm();
    void setAlarm();
    void setCurrentSector(int currentSector);

    int getCurrentSector();

    bool isRSU();
    bool isWaiting();
    bool isRight();
    bool isLeft();

    void setRSU();
    void setWaiting();
    void setRight();
    void setLeft();

    void setSleepFlag(bool flag);

    bool getSleepFlag();


private:
    // Costruttore reso privato per impedire il "new Context()" esterno
    Context();
    
    // Distruttore privato (opzionale, ma coerente per un singleton che non deve essere cancellato con delete)
    ~Context() = default;

    enum RadarState {
        IDLE,
        WORKING,
        PRE_ALARM,
        ALARM
    };
    
    RadarState radarState;

    int currentSector;

    enum ControlSweep {
        RSU,
        WAITING,
        RIGHT,
        LEFT
    };
    ControlSweep controlSweep;

    bool sleepFlag;
};

#endif