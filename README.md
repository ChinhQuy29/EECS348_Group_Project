<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]



<!-- PROJECT HEADER -->
<br />
<div align="center">
  <a href="https://github.com/ChinhQuy29/EECS348_Group_Project"></a>

  <h3 align="center">©Calculatorz, 2026</h3>

  <p align="center">
    Arithmetic Expression Evaluator in C++
    <br />
    <a href="https://github.com/ChinhQuy29/EECS348_Group_Project/tree/main/doc"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/ChinhQuy29/EECS348_Group_Project/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    &middot;
    <a href="https://github.com/ChinhQuy29/EECS348_Group_Project/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation-from-zip">Installation from .zip</a></li>
        <li><a href="#compilation-from-source">Compilation from Source</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This is a Qt-based calculator designed for use during tabletop role-playing games. The UI provides any input the user may need, converts the input into tokens, parses infix to postfix, and evaluates the result (including random values given by dice). It validates syntax and numbers, reports errors with position info, and highlights errors in the session history. Calculations are stored with timestamps in a history file, and the app has both a session history, and persistant history view to browse or clear past entries.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With
[![C++][C++-shield]][C++-url]
[![QT][QT-shield]][QT-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This software was designed to be completely self-contained and has no prerequisite software dependencies.

### Installation from .zip

1. Head over to the .zip file associated with your operating system inside the github repository.
* [![Windows][Windows-shield]][Windows-url]
* [![macOS][macOS-shield]][macOS-url]
<!-- * [![Linux][Linux-shield]][Linux-url] -->

2. Select "Download raw file" and successfully download the zipped folder.
3. Use your prefered decompressing method (7zip, WinRAR, or native decompression).
4. Finally, run the executable from your terminal or user interface to confirm the instalation.

> **Note:** On macOS, you may need to make the binary executable first:
> ```bash
> chmod +x CalcTTRPG
> ```

---

### Compilation from Source

If you'd prefer to compile it yourself, or your operating system has no associated .zip file, you can compile the program yourself.

#### Prerequisites

- A downloaded version of Git Bash
- An account and licence with the Qt software\
_With an email address issued by a higher educational institution, a Qt Educational Licence can be obtained for free through their website._
- A downloaded version of Qt Creator compatible with Qt6
- A C++ compiler (GCC or Clang) compatible with C++17
- The relevent ___deployqt program for your operating system

#### Steps

1. Clone our repository, so you have a local version of the source code.
```bash
git clone https://github.com/ChinhQuy29/EECS348_Group_Project.git
```
2. Launch Qt Creator and select "Open Project...", and use your file explorer to select the `CMakeLists.txt` in the cloned `EECS348_Group_Project/CalcTTRPG-Uncompiled` directory.
3. Deselect the default "Debug" kit, and configure the project as a "Release" kit.
4. Build the project using the UI. Qt should parse the information in the CMake file and build using the specified versions.
At this point you should have the compiled executable and be able to run the program from the Qt Creator UI.
To make the program functional independent of Qt Creator:
5. Separate your generated executable file into it's own directory, then run the relavent ___deployqt program on the executable to generate all the required library files.
Congratulations! You now have your own version of the program.

_If you have performed these steps because there is no associated .zip file in the repository yet, feel free to contribute to improving this repo by zipping a version of the directory and sending it through GitHub to us with information about your operating system (See Contributing section for more information). Then we can add your .zip to the main branch and others can benifit from your contribution._

## Usage
Press buttons, and form expressions! Try things out and see what happens. This calculator was designed to be very user-friendly.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Tokenizer Module
- [x] Parser Module
- [x] Evaluator Module
- [x] History Manager Module
- [x] Error Handler Module
- [x] User Interface Module

See the [open issues](https://github.com/ChinhQuy29/EECS348_Group_Project/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/ChinhQuy29/EECS348_Group_Project/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=ChinhQuy29/EECS348_Group_Project" alt="contrib.rocks image" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

©Calculatorz, 2026
Chase - c754h654@ku.edu
Courtney - c094m918@ku.edu
Eian - e971h440@ku.edu
Isaiah - i804j427@ku.edu
Jason - q595t095@home.ku.edu

Project Link: [https://github.com/ChinhQuy29/EECS348_Group_Project](https://github.com/ChinhQuy29/EECS348_Group_Project)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ChinhQuy29/EECS348_Group_Project.svg?style=for-the-badge
[contributors-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ChinhQuy29/EECS348_Group_Project.svg?style=for-the-badge
[forks-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/network/members
[stars-shield]: https://img.shields.io/github/stars/ChinhQuy29/EECS348_Group_Project.svg?style=for-the-badge
[stars-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/stargazers
[issues-shield]: https://img.shields.io/github/issues/ChinhQuy29/EECS348_Group_Project.svg?style=for-the-badge
[issues-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/issues

<!-- Shields.io badges. You can a comprehensive list with many more badges at: https://github.com/inttter/md-badges -->
[C++-shield]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B
[C++-url]: https://cplusplus.com
[Qt-shield]: https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=qt
[Qt-url]: https://www.qt.io
[Windows-shield]: https://custom-icon-badges.demolab.com/badge/Windows-0078D6?logo=windows11
[Windows-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/tree/main/CalcTTRPG-Windows11.zip
[macOS-shield]: https://img.shields.io/badge/macOS-000000?logo=apple
[macOS-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/tree/main/CalcTTRPG-macOS26.zip
[Linux-shield]: https://img.shields.io/badge/Linux-FCC624?logo=linux
[Linux-url]: https://github.com/ChinhQuy29/EECS348_Group_Project/tree/main/CalcTTRPG-LinuxDebian13.zip
