# **Fossil TLS Library by Fossil Logic**

Fossil TLS is an extensive and versatile library meticulously crafted to manage secure communication across a multitude of platforms. This library offers a comprehensive array of functions dedicated to secure data transmission, efficient encryption management, and detailed error reporting. Developed in the C programming language, Fossil TLS is engineered to support high-performance and reliable TLS operations, ensuring uniform and predictable behavior across various operating systems, including Windows, macOS, and Linux. By leveraging Fossil TLS, developers can achieve consistent and secure communication, making it an indispensable tool for cross-platform software development.

## Key Features

1. **Cross-Platform Compatibility**: Provides consistent TLS operations across major operating systems, including Windows, macOS, and Linux.
2. **Secure Communication**: Includes functions for secure data transmission, preventing common vulnerabilities such as man-in-the-middle attacks and data breaches.
3. **Modular Design**: Comprises separate modules for error handling, encryption, decryption, and certificate management, allowing for easy integration and customization.
4. **Efficient Encryption Handling**: Supports encryption operations with a focus on secure and reliable data transmission.
5. **Error Reporting**: Includes a comprehensive set of error codes and a lookup function to provide detailed error messages.

## Prerequisites

To get started with Fossil TLS, ensure you have the following installed:

- **Meson Build System**: If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).
- **CMake Build System**: If you don’t have CMake installed, follow the installation instructions on the official [CMake website](https://cmake.org/getting-started/).

### Adding Fossil TLS Dependency

#### Adding Fossil TLS Dependency With Meson

1. **Install Meson Build System**:
   Install Meson version `1.3` or newer:

   ```sh
   python -m pip install meson           # To install Meson
   python -m pip install --upgrade meson # To upgrade Meson
   ```

2. **Create a `.wrap` File**:
   Add the `fossil-tls.wrap` file in your `subprojects` directory and include the following content:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-tls.git
   revision = v0.1.0

   [provide]
   fossil-tls = fossil_tls_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil TLS by adding the following line:

   ```ini
   dep = dependency('fossil-tls')
   ```

---

#### Adding Fossil TLS Dependency With CMake

To use Fossil TLS with CMake, follow these steps:

1. **Install CMake**:
   Install CMake version `3.13.4` or newer:

   ```sh
   python -m pip install cmake           # To install CMake
   python -m pip install --upgrade cmake # To upgrade CMake
   ```

2. **Find and Integrate Fossil TLS**:
   After installing CMake, you can integrate Fossil TLS as a dependency. Add the following lines to your `CMakeLists.txt` file:

   ```cmake
   # Find Fossil TLS package
   find_package(FossilTls REQUIRED)

   # Link the Fossil TLS to your project
   target_link_libraries(your_target FossilTls)
   ```

3. **Configure Your CMake Project**:
   Make sure to configure your CMake project to include the necessary paths and dependencies for Fossil TLS. Typically, you’ll want to make sure the `FossilTls` library is correctly linked in your build configuration.

   This will ensure that Fossil TLS is included and properly built with your project.

---

**Note**: For the best experience, always use the latest release of Fossil TLS. Visit the [Fossil TLS Releases](https://github.com/fossillogic/fossil-tls/releases) page for the latest versions.

## Configure Options

Fossil TLS offers configurable options to tailor the build process to your needs:

- **Running Tests**: To enable testing, configure the build with `-Dwith_test=enabled`.

Example:

```sh
meson setup builddir -Dwith_test=enabled
```

## Contributing and Support

For contributions, issue reporting, or support, please open an issue on the project repository or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information. Your feedback and contributions are appreciated.
