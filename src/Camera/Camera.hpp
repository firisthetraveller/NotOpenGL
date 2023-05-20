#ifndef __INTERFACE_CAMERA__
#define __INTERFACE_CAMERA__

template <typename T>
concept is_camera = requires(T camera) {
  {camera.rotateLeft()};
  {camera.rotateUp()};
  {camera.getPosition()};
};

template <is_camera C> class Camera : public C {};

#endif
