#include "Config.h"
#include "Object.h"
#include "Car.h"

class Player : public Object {
  private:
    PlayerConfig m_config;
    Car m_car;

  public:
    Player(PlayerConfig config)
        : Object(config.car_config.start_position), m_car(config.car_config), m_config(config) {}
    void Update(const std::chrono::microseconds& ms) override;
    void Render() override;
    void Render(const Vector2& position) override;
};
