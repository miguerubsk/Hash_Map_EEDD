# Hash Map EEDD

[![C++](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Estado](https://img.shields.io/badge/status-active-brightgreen.svg)]()
<br>
[![Build and Run](https://github.com/miguerubsk/Hash_Map_EEDD/actions/workflows/build.yml/badge.svg)](https://github.com/miguerubsk/Hash_Map_EEDD/actions/workflows/build.yml)
[![CodeQL Advanced](https://github.com/miguerubsk/Hash_Map_EEDD/actions/workflows/codeql.yml/badge.svg)](https://github.com/miguerubsk/Hash_Map_EEDD/actions/workflows/codeql.yml)


## Descripción

Hash Map EEDD es una implementación en C++ de una tabla hash centrada en la clase `Cliente.h` para la gestión eficiente de clientes, con operaciones de inserción, borrado, búsqueda, redispersión y estadísticas de colisiones. El proyecto incluye ejemplos de uso con la clase `Cliente`, gestión de motos y rutas, y estructuras auxiliares como listas e itinerarios.

## Tabla de Contenidos

- [Instalación](#instalación)
- [Uso](#uso)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Contribuir](#contribuir)
- [Licencia](#licencia)
- [Contacto](#contacto)
- [Reconocimientos](#reconocimientos)

## Instalación

1. Clona el repositorio:
   ```sh
   git clone https://github.com/miguerubsk/Hash_Map_EEDD.git
   ```
2. Compila el proyecto con tu compilador C++ favorito:

   ```sh
   g++ main.cpp -o hash_map -std=c++11
   ```

   O usa tu IDE (Code::Blocks, Visual Studio, CLion, etc).

3. Ejecuta el binario generado:
   ```sh
   ./hash_map
   ```

## Uso

- El proyecto implementa una tabla hash genérica (`THashCliente`) con operaciones de inserción, borrado, búsqueda y redispersión.
- Incluye ejemplos de uso con objetos `Cliente`, gestión de motos (`Moto`) y rutas (`Itinerario`).
- Permite cargar datos desde archivos y realizar búsquedas eficientes.
- Puedes modificar el código para probar otras estructuras o tipos de datos.

## Estructura del Proyecto

```
Hash_Map_EEDD/
│
├── THashCliente.h / .cpp  # Implementación de la tabla hash genérica
├── Cliente.h / Cliente.cpp# Definición e implementación de la clase Cliente
├── EcoCityMoto.h / .cpp   # Gestión de clientes y motos
├── Moto.h / Moto.cpp      # Definición e implementación de la clase Moto
├── Itinerario.h / .cpp    # Definición e implementación de la clase Itinerario
├── UTM.h                  # Clase para coordenadas geográficas
├── fecha.h / fecha.cpp    # Clase para fechas y horas
├── main.cpp               # Ejemplo de uso y pruebas
├── LICENSE                # Licencia GNU GPL v3
└── README.md              # Este archivo
```

## Contribuir

Las contribuciones son bienvenidas. Puedes abrir issues para sugerencias o errores, y enviar pull requests con mejoras o nuevas funcionalidades.

## Licencia

Distribuido bajo la Licencia GNU GPL v3. Consulta el archivo `LICENSE.md` para más información.

## Contacto

[Fernando Jiménez Quesada](https://github.com/ferazules1998) y [Miguel González García](https://github.com/miguerubsk)

## Reconocimientos

- [othneildrew/Best-README-Template](https://github.com/othneildrew/Best-README-Template) por la plantilla.
- [shields.io](https://shields.io/) por los badges.
- C++ Standard Library.
