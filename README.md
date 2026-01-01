# Lunar
A language for making quick animations and graphics

## Versions
There are 3 versions, **Windows**, **Linux** and **MacOS**, and as of _1/1/2026_ only the Windows one has been released.

## Usage
- Compile and Use
  ```sh
  # Cloning
  git clone https://github.com/NightNovaNN/Lunar
  cd Lunar

  # Compiling
  gcc lunar.c parse.c -O3 -lgdi32 -o lunar

  # Run
  ./lunar test.ln
  # Or if the file is "script.ln", then just ./lunar will auto run
  ```
- Syntax
  ```lunar
  title <Title>              # Sets title of a window
  clear                      # Clears the screen
  rect <x of the left edge> <y of top edge> <width> <height>
  text <x> <y> <Text>        # Puts text on the screen
  move <steps>               # Makes an object move
  ```
