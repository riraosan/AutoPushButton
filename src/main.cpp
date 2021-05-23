#include <Arduino.h>
#include <Servo.h>
#include <Ticker.h>

class Application {
   public:
    Application() {
        _interval    = 0;
        _period      = 0;
        _init_angle  = 0;
        _push_angle  = 0;
        _port_number = 0;
        _timer       = nullptr;
        _enable_port = false;
    }

    static void push_button(void) {
        _enable_button = true;
    }

    void setServoPortNumber(int portNumber) {
        if (_enable_port == false) {
            _port_number = portNumber;
            _enable_port = true;
        }
    }

    void begin(uint32_t period, uint32_t interval, uint32_t init_angle, uint32_t push_angle) {
        Serial.begin(115200);

        if (_enable_port) {
            _period     = period;
            _interval   = interval;
            _init_angle = init_angle;
            _push_angle = push_angle;

            _servo.attach(_port_number);
            _servo.write(_init_angle);  //off
            delay(1000);
            _timer = new Ticker(push_button, _period, 0, MICROS);
            _timer->start();
        } else {
            Serial.println("Servo port is disable");
        }
    }

    void update(void) {
        if (_timer != nullptr) {
            _timer->update();

            if (_enable_button) {
                _servo.write(_init_angle);  //off
                delay(_interval);

                _servo.write(_push_angle);  //on
                Serial.print("Push Button! Count = ");
                Serial.println(_timer->counter());

                _enable_button = false;
            }
        }
    }

   private:
    uint32_t _interval;
    uint32_t _period;
    uint32_t _init_angle;
    uint32_t _push_angle;
    uint32_t _port_number;
    Servo _servo;
    Ticker* _timer;

    bool _enable_port;
    static bool _enable_button;
};

Application theApp;

bool Application::_enable_button = false;

//Settings
constexpr uint32_t interval   = 3 * 1000;   //3sec)
constexpr uint32_t period     = 15 * 1000;  //12sec
constexpr uint32_t init_angle = 92;         //degree
constexpr uint32_t push_angle = 50;         //degree

void setup(void) {
    theApp.setServoPortNumber(3);
    theApp.begin(period, interval, init_angle, push_angle);
}

void loop(void) {
    theApp.update();
}
