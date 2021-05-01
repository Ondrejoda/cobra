#define SDL_MAIN_HANDLED

#include "cobra.cpp"

const int WIDTH = 1280;
const int HEIGHT = 720;

class GameScene: public Scene {
public:
  Object paddle;
  Object paddle2;
  Object ball;
  int score = 0;
  int score2 = 0;
  int tick = 0;
  Text score_text;
  Text score_text2;
  Particle trail;

  GameScene() {

    paddle = Object(Vector2(25, (HEIGHT + 300) / 2), Vector2(50, 300), "", Color(255));
    paddle.damping = .997;
    add_object(&paddle);

    paddle2 = Object(Vector2(WIDTH - 75, (HEIGHT + 300) / 2), Vector2(50, 300), "", Color(255));
    paddle2.damping = .997;
    add_object(&paddle2);

    ball = Object(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(30, 30), "", Color(255));
    ball.apply_impulse(500, 500);
    ball.damping = 1.000001;
    add_object(&ball);

    score_text = Text("0", "lgc.ttf", 196, Vector2(0, HEIGHT / 2), Color(128), -1);
    add_text(&score_text);

    score_text2 = Text("0", "lgc.ttf", 196, Vector2(WIDTH, HEIGHT / 2), Color(128), -1);
    add_text(&score_text2);

    trail = Particle(Vector2(), 30, Color(255, 128), Color(0, 0), .3);

    Cobra::set_scene(this);
  };

  void main() {
    std::cout << "main" << '\n';
    tick += 1;
    score_text.position.x = lerp(score_text.position.x, 300, .01);
    score_text2.position.x = lerp(score_text2.position.x, WIDTH - 300, .01);
    trail.position = ball.position + Vector2(16, 16);
    if (tick % 10 == 0) {
      add_particle(trail);
    }
    if (ball.position.y <= 0 || ball.position.y + ball.size.y >= HEIGHT) {
      ball.velocity.y = -ball.velocity.y;
    };
    if (Cobra::detect_collision(&ball, &paddle) || Cobra::detect_collision(&ball, &paddle2)) {
      ball.velocity.x = -ball.velocity.x;
    };
    if (ball.position.x < -32) {
      ball.position = Vector2(WIDTH / 2, HEIGHT / 2);
      score2++;
    };
    if (ball.position.x > WIDTH + 2) {
      ball.position = Vector2(WIDTH / 2, HEIGHT / 2);
      score++;
    };
    if (Cobra::keyboard[SDL_SCANCODE_W]) {
      paddle.apply_impulse(0, -5);
    };
    if (Cobra::keyboard[SDL_SCANCODE_S]) {
      paddle.apply_impulse(0, 5);
    };
    if (Cobra::keyboard[SDL_SCANCODE_UP]) {
      paddle2.apply_impulse(0, -5);
    };
    if (Cobra::keyboard[SDL_SCANCODE_DOWN]) {
      paddle2.apply_impulse(0, 5);
    };
    if (paddle.position.y != clamp(paddle.position.y, 0, HEIGHT - paddle.size.y)) {
      paddle.position.y = clamp(paddle.position.y, 0, HEIGHT - paddle2.size.y);
      paddle.velocity.y = 0;
    };
    if (paddle2.position.y != clamp(paddle2.position.y, 0, HEIGHT - paddle2.size.y)) {
      paddle2.position.y = clamp(paddle2.position.y, 0, HEIGHT - paddle2.size.y);
      paddle2.velocity.y = 0;
    };
    score_text.text = std::to_string(score);
    score_text2.text = std::to_string(score2);
    ball.position.y = clamp(ball.position.y, 0, HEIGHT - 30);
  };
};

class IntroScene: public Scene {
public:
  Text title;
  Text sub;

  IntroScene() {
    Cobra::set_scene(this);

    title = Text("CPong", "lgc.ttf", 128, Vector2(WIDTH / 2, 0), Color(255), -1);
    add_text(&title);

    sub = Text("W, S or Up, Down to control | Press ENTER to continue", "lgc.ttf", 32, Vector2(WIDTH / 2, HEIGHT), Color(128), -1);
    add_text(&sub);
  };

  void main() {
    title.position.y = lerp(title.position.y, HEIGHT / 2, .01);
    sub.position.y = lerp(sub.position.y, 600, .01);
    if (Cobra::keyboard[SDL_SCANCODE_RETURN]) {
      running = false;
      GameScene gs;
    };
  };
};

int main(int argc, char const *argv[]) {
  Cobra::init(Color(0), Vector2(WIDTH, HEIGHT));

  IntroScene is;
  Cobra::mainloop();

  return 0;
};
