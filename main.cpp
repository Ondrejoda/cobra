#define SDL_MAIN_HANDLED

#include "cobra.cpp"

int main(int argc, char const *argv[]) {
  Engine cobra(Color(0, 0, 0, 255), Vector2(1920, 1080));
  cobra.set_fullscreen(true);

  SFX bump("test.wav");

  Object paddle(cobra.renderer, Vector2(50, 340), Vector2(50, 400), "", Color(255, 255, 255, 255));
  paddle.damping = .997;
  cobra.add_object(&paddle);

  Object paddle2(cobra.renderer, Vector2(1820, 340), Vector2(50, 400), "", Color(255, 255, 255, 255));
  paddle2.damping = .997;
  cobra.add_object(&paddle2);

  Object top_boundary(cobra.renderer, Vector2(0, -50), Vector2(1920, 50), "", Color(255, 255, 255, 255));
  cobra.add_object(&top_boundary);

  Object bottom_boundary(cobra.renderer, Vector2(0, 1080), Vector2(1920, 50), "", Color(255, 255, 255, 255));
  cobra.add_object(&bottom_boundary);

  Object ball(cobra.renderer, Vector2(960, 540), Vector2(30, 30), "", Color(255, 255, 255, 255));
  ball.apply_impulse(500, 500);
  ball.damping = 1.00001;
  cobra.add_object(&ball);

  int score = 0;
  int score2 = 0;

  Text score_text("0", "lgc.ttf", 256, Vector2(400, 540), Color(128, 128, 128, 255));
  cobra.add_text(&score_text);

  Text score_text2("0", "lgc.ttf", 256, Vector2(1520, 540), Color(128, 128, 128, 255));
  cobra.add_text(&score_text2);

  Particle trail(Vector2(), 30, Color(255, 255, 255, 255), Color(0, 0, 0, 0), .3);

  int tick = 0;

  while (true) {
    tick += 1;
    cobra.start_frame();
    if (cobra.handle_all()) {
      break;
    };
    trail.position = ball.position + Vector2(16, 16);
    cobra.add_particle(trail);
    if (cobra.detect_collision(&ball, &top_boundary)) {
      ball.velocity.y = -ball.velocity.y;
      cobra.play_sfx(bump);
    };
    if (cobra.detect_collision(&ball, &bottom_boundary)) {
      ball.velocity.y = -ball.velocity.y;
      cobra.play_sfx(bump);
    };
    if (cobra.detect_collision(&ball, &paddle)) {
      ball.velocity.x = -ball.velocity.x;
      cobra.play_sfx(bump);
    };
    if (cobra.detect_collision(&ball, &paddle2)) {
      ball.velocity.x = -ball.velocity.x;
      cobra.play_sfx(bump);
    };
    if (ball.position.x < -32) {
      ball.position = Vector2(960, 540);
      score2++;
    };
    if (ball.position.x > 1922) {
      ball.position = Vector2(960, 540);
      score++;
    };
    if (cobra.keyboard[SDL_SCANCODE_W]) {
      paddle.apply_impulse(0, -5);
    };
    if (cobra.keyboard[SDL_SCANCODE_S]) {
      paddle.apply_impulse(0, 5);
    };
    if (cobra.keyboard[SDL_SCANCODE_UP]) {
      paddle2.apply_impulse(0, -5);
    };
    if (cobra.keyboard[SDL_SCANCODE_DOWN]) {
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
    cobra.end_frame();
  };
  return 0;
};
