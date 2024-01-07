# Jakaś fajna gierka
SFML 2.6.1, Visual Studio 2022
9.12.2024 - wgranie biblioteki SFML do Visual Studio 2022, tworzenie okienka, tworzenie spadających kwadracików
10.12.2024 - spadające kwadraty- przyciśnięcie myszy usuwa kwadrat(uniemożliwienie usunięcia przy przytrzymywaniu myszy), spadnięcie poza ekran zabiera życie, trafienie zwiększa punkty

Do zbudowania projektu:
cmake -S . -B build_win64 -D CMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022"
cmake --build .\build_win64\Release --config Release
