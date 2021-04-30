#define SDL_MAIN_HANDLED

#include "cobra.cpp"

const int WIDTH = 1920;
const int HEIGHT = 1080;

class IntroScene: public Scene {
public:
  Engine* cobra;
  Text title;
  Text sub;

  void ready(Engine* engine) {
    cobra = engine;

    title = Text("PonG", "lgc.ttf", 256, Vector2(WIDTH / 2, 0), Color(255), -1);
    add_text(&title);

    sub = Text("Press ENTER to continue", "lgc.ttf", 64, Vector2(WIDTH / 2, HEIGHT), Color(128), -1);
    add_text(&sub);
  };

  void main() {
    title.position.y = lerp(title.position.y, 400, .01);
    sub.position.y = lerp(sub.position.y, 600, .01);
    if (cobra->keyboard[SDL_SCANCODE_RETURN]) {
      running = false;
    };
  };
};


class GameScene: public Scene {
public:
  Engine* cobra;
  SFX bump;
  Object paddle;
  Object paddle2;
  Object ball;
  int score;
  int score2;
  int tick;
  Text score_text;
  Text score_text2;
  Particle trail;

  void ready(Engine* engine) {
    cobra = engine;

    bump = SFX("test.wav");

    paddle = Object(Vector2(50, 340), Vector2(50, 400), "", Color(255));
    paddle.damping = .997;
    add_object(&paddle);

    paddle2 = Object(Vector2(1820, 340), Vector2(50, 400), "", Color(255));
    paddle2.damping = .997;
    add_object(&paddle2);

    ball = Object(Vector2(960, 540), Vector2(30, 30), "", Color(255));
    ball.apply_impulse(500, 500);
    ball.damping = 1.00001;
    add_object(&ball);

    score = 0;
    score2 = 0;

    score_text = Text("0", "lgc.ttf", 256, Vector2(400, 540), Color(128), -1);
    add_text(&score_text);

    score_text2 = Text("0", "lgc.ttf", 256, Vector2(1520, 540), Color(128), -1);
    add_text(&score_text2);

    trail = Particle(Vector2(), 30, Color(255, 128), Color(0, 0), .3);
    tick = 0;
  };

  void main() {
    tick += 1;
    trail.position = ball.position + Vector2(16, 16);
    if (tick % 3 == 0) {
      add_particle(trail);
    }
    if (ball.position.y <= 0) {
      ball.velocity.y = -ball.velocity.y;
      cobra->play_sfx(bump);
    };
    if (ball.position.y + ball.size.y >= 1080) {
      ball.velocity.y = -ball.velocity.y;
      cobra->play_sfx(bump);
    };
    if (cobra->detect_collision(&ball, &paddle)) {
      ball.velocity.x = -ball.velocity.x;
      cobra->play_sfx(bump);
    };
    if (cobra->detect_collision(&ball, &paddle2)) {
      ball.velocity.x = -ball.velocity.x;
      cobra->play_sfx(bump);
    };
    if (ball.position.x < -32) {
      ball.position = Vector2(960, 540);
      score2++;
    };
    if (ball.position.x > 1922) {
      ball.position = Vector2(960, 540);
      score++;
    };
    if (cobra->keyboard[SDL_SCANCODE_W]) {
      paddle.apply_impulse(0, -5);
    };
    if (cobra->keyboard[SDL_SCANCODE_S]) {
      paddle.apply_impulse(0, 5);
    };
    if (cobra->keyboard[SDL_SCANCODE_UP]) {
      paddle2.apply_impulse(0, -5);
    };
    if (cobra->keyboard[SDL_SCANCODE_DOWN]) {
      paddle2.apply_impulse(0, 5);
    };
    if (paddle.position.y != clamp(paddle.position.y, 0, 680)) {
      paddle.position.y = clamp(paddle.position.y, 0, 680);
      paddle.velocity.y = 0;
    };
    if (paddle2.position.y != clamp(paddle2.position.y, 0, 680)) {
      paddle2.position.y = clamp(paddle2.position.y, 0, 680);
      paddle2.velocity.y = 0;
    };
    score_text.text = std::to_string(score);
    score_text2.text = std::to_string(score2);
    ball.position.y = clamp(ball.position.y, 0, 1050);
  };
};

int main(int argc, char const *argv[]) {
  Engine cobra(Color(0), Vector2(WIDTH, HEIGHT));
  cobra.set_fullscreen(true);

  IntroScene is;
  is.ready(&cobra);
  cobra.set_scene(&is);

  while (is.running) {
    cobra.start_frame();
    if (cobra.handle_all()) {
      break;
    };
    is.main();
    cobra.end_frame();
  };

  GameScene gs;
  gs.ready(&cobra);
  cobra.set_scene(&gs);

  while (gs.running) {
    cobra.start_frame();
    if (cobra.handle_all()) {
      break;
    };
    gs.main();
    cobra.end_frame();
  };
  return 0;
};
