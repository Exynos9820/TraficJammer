#include "Config.h"
#include "Object.h"
#include "Car.h"
#include <raylib.h>

class Player : public Object {
  private:
    PlayerConfig m_config;
    Car m_car;
    Vector2 delta;

  public:
    Player(PlayerConfig config)
        : Object(config.car_config.start_position), m_car(config.car_config), m_config(config),
          delta({0, 0}) {}
    void Update(const std::chrono::microseconds& ms) override;
    void Render() override;
    const Collider GetCollider() override;
    void Stop() override { m_car.m_current_speed = 0; };
    const ColliderType& GetColliderType() override { return m_car.GetColliderType(); }
    const Vector2 GetMoveVector(const std::chrono::microseconds& ms);
    void Move(const Vector2& move_vector) override {
        m_car.m_position += move_vector;
        delta += move_vector;
    }
};
