[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/kkuchar2/openglengine">
    	🎉
  </a>

  <h3 align="center">openglengine</h3>

  <p align="center">
    Project as integration of OpenGL rendering system into graphical user interface. Used for testing, learning and experimentation.
    <br />
    <br />
    <a href="https://github.com/kkuchar2/openglengine/issues">Report Bug</a>
        ·
    <a href="https://github.com/kkuchar2/openglengine/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [Getting Started](#getting-started)
* [Contributing](#contributing)
* [License](#license)

<!-- GETTING STARTED -->
## Getting Started

1. Clone the repo

  ```sh
    git clone --recurse-submodules -j8 https://github.com/kkuchar2/openglengine
  ```

2. Build

  ```sh

    # Make sure you've gcc, g++, xorg-dev and libglu1-mesa-dev installed on Linux

    cd openglengine
    mkdir build
    cd build
    cmake ..
    make -j8
  ```

3. Run
```sh
  ./openglengine

  # You should see split view of rotating colorful particles.
  # By pressing and holding right mouse button and moving mouse look around.
  # WASD to move camera
  # Hold left SHIFT to speed up movement.
```

## Contributing

Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/kkuchar2/openglengine.svg?style=flat-square
[contributors-url]: https://github.com/kkuchar2/openglengine/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kkuchar2/openglengine.svg?style=flat-square
[forks-url]: https://github.com/kkuchar2/openglengine/network/members
[stars-shield]: https://img.shields.io/github/stars/kkuchar2/openglengine.svg?style=flat-square
[stars-url]: https://github.com/kkuchar2/openglengine/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=flat-square
[issues-url]: https://github.com/kkuchar2/openglengine/issues
[license-shield]: https://img.shields.io/github/license/kkuchar2/openglengine?style=flat-square
[license-url]: https://github.com/kkuchar2/openglengine/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/kkuchar/
[product-screenshot]: images/screenshot.png
