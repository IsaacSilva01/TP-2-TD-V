# README

## Requisitos

El proyecto fue desarrollado y probado en:

- **Sistema Operativo:** Ubuntu 22.04.4 LTS
- **Compilador:** GCC 11.2.0 con soporte para C++17
- **Herramienta de construcción:** Make

## Compilación

Para compilar el proyecto ejecutar:

```bash
make clean && make
```

Esto genera el ejecutable:

```bash
./gap_simulator
```

## Ejecución

Para ejecutar el programa:

```bash
./gap_simulator
```

Por simplicidad de uso durante el desarrollo, se optó por una interfaz interactiva en lugar de recibir argumentos por línea de comandos.

Al iniciarse, el programa muestra un menú interactivo que permite:

1. Seleccionar una instancia.
2. Ejecutar una heurística constructiva.
3. Ejecutar una búsqueda local a partir de una solución inicial.
4. Ejecutar la metaheurística GRASP.
5. Cambiar la instancia seleccionada.
6. Salir del programa.

## Formato de las instancias

Las instancias benchmark utilizadas siguen la nomenclatura:

```
g<categoria><m>x<n>
```

donde:

- `g` indica que se trata de una instancia del problema GAP.
- `<categoria>` $\in \{a, b, e\}$ identifica el conjunto al que pertenece la instancia.
- `<m>` representa la cantidad de depósitos.
- `<n>` representa la cantidad de vendedores.

Por ejemplo:

- `ga5x100`: instancia de la categoría A con 5 depósitos y 100 vendedores.
- `gb20x200`: instancia de la categoría B con 20 depósitos y 200 vendedores.
- `ge80x1600`: instancia de la categoría E con 80 depósitos y 1600 vendedores.

Para la instancia real, se la definió como `real1100x310`, dado que tiene 310 depósitos y 1100 vendedores.

Las instancias benchmark se encuentran almacenadas en:

```
instances/gap/gap_a/
instances/gap/gap_b/
instances/gap/gap_e/
```

mientras que la instancia real se encuentra en:

```
instances/real/
```

El programa solicita además el nombre del archivo de salida donde se almacenará la solución obtenida. Dicho archivo se guarda en el directorio:

```
respuestas/
```

## Heurísticas implementadas

El programa permite ejecutar las siguientes heurísticas constructivas:

- Greedy por vendedores (costo mínimo).
- Greedy por depósitos (costo mínimo + flexibilidad).
- Greedy randomizado (top-$k$ random).

En el caso del greedy randomizado y de GRASP, se solicita además ingresar el parámetro $k$, que representa la cantidad de mejores depósitos factibles considerados para seleccionar aleatoriamente la asignación de cada vendedor.

## Búsqueda local

Se implementaron dos operadores de búsqueda local:

- Relocate.
- Swap.

La búsqueda local puede aplicarse sobre cualquiera de las tres heurísticas constructivas disponibles.

## Metaheurística

Se implementó una metaheurística GRASP basada en:

1. Construcción de una solución inicial mediante el greedy randomizado.
2. Aplicación secuencial de los operadores Swap y Relocate.
3. Conservación de la mejor solución encontrada luego de un número máximo de iteraciones dado por:

$$\min(500, 10n)$$

donde $n$ es la cantidad de vendedores de la instancia.
