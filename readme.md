## 📌 Can this project run outside Qt Creator?

### ✔ Yes, it can run on any system with a C++ compiler.

Even though the project was created in **Qt Creator**, the code is still just **standard C++**, so it can run in any terminal or IDE.

Below is a more detailed, step-by-step explanation.

---

## ✅ **1. Running the Project in Qt Creator (FULL DETAILED STEPS)**

### 🔹 Step 1: Open Qt Creator
- Double-click on **Qt Creator** icon.
- Wait for it to load.

### 🔹 Step 2: Open Your Project
1. Click on **File** (top-left).
2. Select **Open File or Project…**
3. A file dialog will open.
4. Now choose one of the following files depending on your project type:
   - If your project uses qmake → select the **.pro** file  
     Example: `myproject.pro`
   - If your project uses CMake → select **CMakeLists.txt**
   - If you created a simple project → select the **folder** containing your `.cpp` files

5. Click **Open**.

### 🔹 Step 3: Select a Kit (VERY IMPORTANT)
After opening, Qt Creator will show a window called **Configure Project**.

You must select a build kit here:

Choose:
✔ **Desktop Qt 5.x GCC (or MinGW)**  
OR  
✔ **Desktop Qt 6.x GCC**

(Any *Desktop* kit works.)

Then click:
➡ **Configure Project**

### 🔹 Step 4: Build the Project
- Click the **Hammer (🔨)** icon on the left bottom bar  
  OR  
- Press **Ctrl + B**

Qt Creator will compile your program.

### 🔹 Step 5: Run the Project
- Click the **Green Run button (▶)** on the bottom-left  
  OR  
- Press **Ctrl + R**

A terminal window will open inside Qt Creator, and your program will start running.

---

## ✅ **2. Running the Project in Any Terminal (Without Qt Creator)**

### 🔹 Step 1: Install a C++ Compiler
You must have one of the following installed:
- **GCC / g++** (Linux, Windows with MinGW/MSYS2, Mac)
- **Clang**
- **MSVC** (Visual Studio)

### 🔹 Step 2: Open Terminal
Windows → CMD / PowerShell  
Linux → Terminal  
Mac → Terminal

### 🔹 Step 3: Navigate to the project folder
Use `cd` command:

```bash
cd path/to/your/project

Linux/Mac:
cd ~/Desktop/myproject
Check files:
ls (or dir on Windows)
```
### 🔹 Step 4: Compile the Program

This converts your .cpp files into an executable.
✅ If your project has only one .cpp file:
```bash
g++ main.cpp -o myapp
```
✅ If your project has multiple .cpp files:
```bash
g++ *.cpp -o myapp
```
If there are no errors, the compiler will generate:
```bash
myapp.exe (Windows)
myapp (Linux/Mac)
```