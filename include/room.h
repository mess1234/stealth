#ifndef __ROOM_H
#define __ROOM_H
/**
 * @file room.h
 * @brief Room module.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "vector.h"

#define MIN_SIDE 9
#define DOOR_SIZE 3
#define NB_GUARDS 5
#define NB_RELIC 3

#define ROOM_HEIGHT 45
#define ROOM_WIDTH 60

typedef enum _Cell
{
    MANA_ON,
    MANA_OFF,
    RELIC_ON,
    RELIC_OFF,
    WALL,
    DOOR
} Cell;

typedef struct _Room
{
    Cell **cells;
    int remaining_relics;
} Room;

/**
 * @brief Create a room cells object
 * 
 * @return Cell** return 2D array of Cells
 */
Cell **create_room_cells(void);

/**
 * @brief Freeing memory of Cells.
 * 
 * @param cells 2D array of Cells.
 */
void free_room_cells(Cell **cells);

/**
 * @brief Place walls inside Room.
 * 
 * @param cells 2D array of Cells.
 */
void place_walls(Cell **cells);

/**
 * @brief Placing reclics inside of Room.
 * 
 * @param room_p Pointer to room.
 * @param player_start Vector of player starting position.
 */
void place_relics(Room *room_p, Vector player_start);

/**
 * @brief Making doors in walls.
 * 
 * @param cells 2D Array of Cells.
 */
void clean_doors(Cell **cells);

#endif /* __ROOM_H */