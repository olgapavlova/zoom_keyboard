/*

  Эксперимент с подключением одной кнопки к Digispark.
  Измеряем, сколько нужно памяти.

*/

#include <DigiKeyboard.h>

#define PIN_BUTTON  0

// Класс работы с кнопкой
class ZoomButton {
  public:
    ZoomButton(int pin, void (*function)()) {
      _pin = pin;
      _react_on_press_pointer = *function;
      pinMode(_pin, INPUT);
    }

    void check_and_react() { // TODO разбить на две функции, а то в этой два действия, перегруз
      _update_current_state();
      // Serial.println(_pressed_flag);
      // Serial.println(_current_state);

      // TODO Перевести два if на switch (just-функцию тоже можно оставить одну)
      if (_just_pressed()) {
          _pressed_flag = true;  // TODO так неаккуратно, надо как-то иначе сделать
          _react_on_press();
      }

      if (_just_released()) { _pressed_flag = false; }
    }

  private:
    int _pin;  // ?TODO выбрать тип попроще
    bool _pressed_flag = false;  // флаг состояния
    bool _current_state = LOW;  // нажатость кнопки
    
    void (*_react_on_press_pointer)();  // указатель на функцию-обработчик нажатия
    void _react_on_press() { (*_react_on_press_pointer)(); }  // обёртка указателя на функцию-обработчик нажатия

    void _update_current_state() {
      _current_state = !digitalRead(_pin); // инверсия из-за подтяжки к 5 В
    }

    bool _just_pressed() {  // проверка, что кнопка только что нажата
      return (_current_state && !_pressed_flag);
    }

    bool _just_released() {  // проверка, что кнопка только что отпущена
      return (!_current_state && _pressed_flag);
    }

};

// функция-обработчик кнопки
void click_button_on_off();

// кнопки с привязкой к Zoom-функциональности
ZoomButton buttonButton(PIN_BUTTON, click_hand_on_off);

/*
  СТАРТ ПРОГРАММЫ
*/
void setup() {
  // pinMode(pinLED, OUTPUT);
  // digitalWrite(pinLED, HIGH);
  // Serial.begin(9600);
  //Keyboard.press(' ');
  //Keyboard.releaseAll();
}

/*
  ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ
*/
void loop() {
  buttonButton.check_and_react();
}

/*
  ФУНКЦИИ РЕАКЦИИ НА КНОПКИ
*/

// TODO шаблонизировать функции нажатия горячих клавиш

// поднять-опустить руку
void click_button_on_off() {
  DigiKeyboard.write('1');
  DigiKeyboard.releaseAll();
}