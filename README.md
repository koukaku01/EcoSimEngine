# EcoSimEngine
![License](https://img.shields.io/github/license/czlin7/EcoSimEngine)

**EcoSimEngine** is a modular ecosystem simulation engine developed in C++20. It leverages SFML 3.0.0 for graphics rendering and nlohmann::json 3.12.0 for configuration management. The engine employs an Entity-Component-System (ECS) architecture to simulate complex interactions within a 2D environment.

### 📦 Features
- **ECS Architecture**: Utilizes components like `CHealth`, `CBehavior`, and `CTransform` to define entity attributes and behaviours.
- **Modular Design**: Easily extendable with additional components and systems.
- **2D Rendering**: Powered by SFML 3.0.0 for efficient graphics handling.
- **JSON Configuration**: Structured configuration files for environment and simulation settings.

### 🔧 Dependencies
- **C++20**: Ensure your compiler supports C++20 features.
- **[SFML 3.0.0](https://www.sfml-dev.org/download/sfml/3.0.0/)**: For GUI with graphics, window, and audio functionalities.
- **[nlohmann::json 3.12.0](https://github.com/nlohmann/json/releases/tag/v3.12.0)**: For parsing and handling JSON configuration files.
  - I decide use `json` file instead of plain `txt` file for configuration, because it is more structured and easier to manage. 

### 🗂 Project Structure
```make
EcoSimEngine/
├── config/               # JSON configuration files
├── include/              # Header files
├── resources/            # Fonts, textures, and other assets
├── src/                  # Source files
├── EcoSimEngine.sln      # Visual Studio solution file
├── EcoSimEngine.vcxproj  # Visual Studio project file
├── LICENSE               # Project license
└── README.md             # Project documentation
```

### 🛠 Installation & Build

1. Clone the Repository:
```
git clone -b prototype https://github.com/czlin7/EcoSimEngine.git
cd EcoSimEngine
```
2. Open the Project:
   - **Visual Studio**: Open `EcoSimEngine.sln`
   - **Other IDEs**: Open the project using the appropriate project file.
3. Configure Dependencies:
   - Ensure SFML 3.0.0 and nlohmann::json 3.12.0 are correctly linked in your project settings.
4. Build the Project:
   - Select the desired configuration (`Debug` or `Release`) and build the project.

### 🤝 Contributing
We welcome contributions to EcoSimEngine! To contribute:

1. **Fork the repository** to your own GitHub account.
2. **Create a new branch** for your feature or bug fix:
```
git checkout -b feature/YourFeatureName
```
3. **Make your changes** in the branch. Follow existing ECS structure and coding style.
4. **Commit your changes** with clear, descriptive messages. Use prefixes like `[feat]:` or `[fix]:`.
```
git commit -m "[feat]: Add CBehavior component"
```
5. **Push your branch** to your fork:
```
git push origin feature/YourFeatureName
```
6. **Open a Pull Request** against the `prototype` branch of the main repository.
    - **Guidelines:**
      - Ensure your code builds and passes any existing tests.
      - Keep commits small and focused.
      - Include comments and documentation for new functionality.


### 📄 License
This project is licensed under the [GPL-3.0 License](LICENSE).
