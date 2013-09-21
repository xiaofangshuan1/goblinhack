/*
 *
 *
  Cellular Automata Method for Generating Random Cave-Like Levels


      From RogueBasin

Jump to: navigation < #column-one>, search < #searchInput>

By Jim Babcock < /index.php?title=Jim_Babcock&action=edit>

It is an old and fairly well documented trick to use cellular automata
 < /index.php?title=Cellular_automata > to generate forest-like structures.
The basic idea is to fill the map randomly, then repeatedly apply the
4-5 rule: a tile is a wall if it is a wall and has 4 neighbors that are
walls, or if it is not a wall and has 5 neighbors that are. This rule
can be stated more simply: a tile becomes or remains a wall if the 3x3
region centered on it contains at least 5 walls. (/Note: It is important
to do this for each tile simultaneously. If you update one, then use its
value when you update the next, your results won't look as good, and the
tricks described later won't work./)

If the map initially contains 45% walls, and the process above is
repeated 5 times, the output looks like (for example)

############################################################
###....####################################.....############
##......######################..#########.........##########
##......#####################....#######...........####.####
##......###################.........................##...###
##......##################..........................###...##
#........##############.............................###...##
#........#############...............................#....##
##.......##############..................................###
##.......###..############..............................####
##.......##....############.............................####
#..............############...###........................###
#...............###########..#####...............##.......##
#................#################...............##.......##
##.....#####..........###########....#..........###.......##
##....#######...........########....###.........####......##
##....#######............######....####........#####......##
##....#######.............####....#####.......#####......###
#......######..............###....####........####......####
#.......######.............###...####.........###.......####
#........#####.............###..####.....................###
##........####..............#...####.....................###
#####......##...................####.....................###
######...........................##.....................####
######..................................................####
######.........###.....................####.............####
######......#########.................######............####
#######....#############.......##############.....###..#####
##############################################..############
############################################################

The problem is, the results of the algorithm are very inconsistent. Not
only is it prone to generating disjoint (not connected) maps, like in
this example, with the same parameters:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########.#####..............#
#####.......#########..###.....###############.............#
####.............#####.###....###################.........##
###...............########...####################........###
##.................#######...####################........###
##.......##.........#####.....##################.........###
##......####.........###.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########....######..#####......#####.....##########......###
#######......#############.....#####.....###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####..........######.....###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

it also sometimes generates maps which consist of basically one huge
open space, like this one:

############################################################
############################################################
#################.####.######..######........###############
########...#####...##...####....####..........######...#####
###.####...####....###..####....####..........#####.....####
##...###....##.....###...##.....###............###......####
###.####...........###..........###.....###.........########
########...........###...........#.......#.........#########
#######.............#..............................#########
######.....##..........................................#####
###.......###...........................................####
##.......####...........................................####
##......................................................####
##.....................................................#####
##.....................................................#####
#.....................................##...............#####
#.....................................##................####
#...........................###......###................####
##...........###............###.....#####...............####
###...........#..............##.....######............######
######.......................##......######........#########
##########..................##.........#####......##########
###########................###..........####......##########
############................#...........####......##########
###.....#####.........##...............#####.......####..###
###.....#####.......#####.............#####..............###
###.....####.......#####..............#####.....##.......###
####...#####.......#####.....#####...######....####.....####
#############.##########....################..##############
############################################################

We can fix the disjoint segments problem in one of three ways. Either
throw away maps that have disjoint segments in them, connect up the
segments after the fact, or fill in all but the biggest segment. We
can't just retry when we get a disjoint map, because if the map is big
then, statistically, that will be almost 100% of the time. Filling in
all but the biggest segment will tend to produce a small area in a map
that was supposed to be big. Connecting up the regions works, but it
tends to look unnatural, as in the example from above, now connected:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########....................#
#####.......#########..###.....###############.............#
####.............####..###....###################.........##
###...............###.####...####################........###
##.................##.####...####################........###
##.......##.........#.###.....##################.........###
##......####..........##.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########............#####......#####.....##########......###
#######......#############...............###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####.....................###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

The solution to both problems, as it turns out, is to revisit the
original cellular automata rules. Recall that the original rule was

    * There is a wall initially at P with 45% probability
    * In the next generation, there is a wall at spot P if the number of
      tiles around P which are walls is at least 5

Or, in more compact notation:

    * Winit (p) = rand[0,100) <  45
    * R (p) = the number of tiles within 1 step of p which are walls
    * W? (p) = R (p) ? 5

Now, one of the problems was that we tend to get big, open areas. So why
not try filling those areas in? Change the rule to

    * W? (p) = R (p) ? 5 or p is in the middle of an open space

Or more formally,

    * Rn (p) = the number of tiles within n steps of p which are walls
    * W? (p) = R1 (p)?5 || R2 (p)=0

So how does it look?

Winit (p) = rand[0,100) <  45
Repeat 5: W? (p) = R1 (p) ? 5 || R2 (p) ? 1

############################################################
##....######################################################
#.......###..#####..####....###########################..###
#...#.........###.............##########..############....##
##...###...#..###..............########....######..###....##
###...######...#..##...........######.....######....###..###
####..######......##..##........####...#..######....########
####..###.#.......#...##...#.....##...###..######...########
#####.........##...........##........####.....##.....#######
#####.........##...........#.......##.....#.............####
####...###...##................#...##......###...........###
####...###..##...###....##.....##..##..##..###....##.....###
#########..###..####...###.............###..##..####.....###
########...##..#####...##...............#...#...####....####
#######........######......###...##....................#####
#######..##.....######....##########...................#####
######..####.......####...#########...................######
####....####..##....##.....#######...##..............#######
###.....###..#####......#...####....##................######
##..##..###..###........##.........#....#......##......#####
#..####..##...##.................###...##.....####......####
#.....#..###..#..##..........#..###..###.....#####......####
##.......####.....#...##........##..###....#######......####
######....###.......................###...#######....#######
#######......................##.....###...#######...########
########.................#######....####...#####....########
########..............###########..######...........########
#########....####....######################........#########
###################.########################################
############################################################

This is more interesting - it doesn't have any big open areas, it has a
decent layout. It's almost fully connected. Still, it has some new
problems: there are isolated single-tile walls in places, and in general
it's not very smooth. But with a little tweaking:

Winit (p) = rand[0,100) <  40
Repeat 4: W? (p) = R1 (p) ? 5 || R2 (p) ? 2
Repeat 3: W? (p) = R1 (p) ? 5

############################################################
###...###########..#############################.....#######
##..........####....################..#########.........####
##...........##.....####..#########.......####..######...###
##.......#..........###....###.................########..###
##......###........###........................#########..###
##.......##.........#........................##########...##
##.......###...........##.............###....#########.....#
##.......######.......####...........#####....#####........#
###.....#########....#####...........######...#####........#
###########################...........#####...#######.....##
#############...###########.............##....########....##
############.........#######...................#######....##
###########...........########......###............##....###
###..#####.............#########...##########............###
##....###...............######################..........####
###..........................######..#########..........####
####..........................###.....#######...........####
####.................##................##................###
####...###..........####...............#..................##
###...#####.........####..............##......##...........#
##....########......#####............####....####..........#
##....#########.....#####............####....####..........#
##.....######.......#####.............##.....####...##.....#
##......##..........#####....................####..####....#
###.................####.........###........############..##
###............##..######.###...############################
####..........##############################################
######..####################################################
############################################################

Notice that the initial fill percentage is a little lower, the cutoffs
are different, and we switch rules after a few generations. This is more
like the desired result. So, with these parameters, I give you some more
samples, at various sizes.

##############################
##..###....###.....###########
#...........................##
#.................##.........#
##..###..........#######.....#
########.........#######.....#
############......####......##
#############...............##
###..########...............##
##....#######...###..#......##
##.....######...#######.....##
##......#####...######......##
##...#...###....#####.......##
##..##.........######.......##
##..........##########......##
###........#####..####.....###
###........####....###.....###
###....##...##.....###.....###
###...####........####......##
###...#####......#####......##
##....#####.....#####.......##
##.....###.....####.........##
##..............##..........##
###.........................##
####........................##
####.......................###
####..........##...........###
#####...###..####.........####
####################.....#####
##############################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####................####..#
######.......#######....###......####..........###..#####..#
#####........######.....######....##..........##########...#
######........###........######...............########.....#
##########...............#######.............########.....##
#############...#######..###########...#####################
############################################################

################################################################
#######..#####............####..####...###....###########...####
###......####..................................#########.....###
##.......###.......................................####......###
##......####.............##.........................##......####
##......#####......##...####................##..............####
##......##############..#####...............###.............####
##.....###############...#####...............##........##...####
##.....################..######.........#.............####...###
##.....################...#####........###............####....##
###.....#####..##...##....####.........###.............###....##
####....####..............###..........###...................###
####....####.............####..........##....................###
###.....####...........#####.........................##.....####
##.......##............#####....................##..####...#####
##.....................######................###########...#####
###..##........##......###############.....############....#####
########......####....#################..###############..######
#########...####################################################
################################################################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####.........##.....####..#
#####........#######....###......####........#####..#####..#
####........#######.....######...#####.......############..#
####.......######..........####..#########..#############..#
###........#####............###..########################.##
##.........####.............###..################.######..##
#....###...####......####....#...######..#######...#####..##
#.....#.....##......######.......#####....#####....#####..##
#...................######........####....###.....#####...##
#....................#####........#####..###......##......##
#....................######........########................#
##......#............########.......#######................#
##......##...........#########......#######...............##
###.....#............####...##.....#######..##...........###
###..........#......####...........######..####..........###
##..........####....####...........#####..######.........###
##...........####..#####............##....######.........###
##............###..######......#...........####..........###
##............###..#######.....##........................###
##.......###...#....#######....#..........................##
###......###.........######.........................##.....#
###.......#..........######........#####...........####....#
###............###...######......########.........#####....#
###...........#####..######.....#########.........####.....#
###...........#####.#######.....########...........###.....#
###...........####..########...#########......##...###....##
###...........####...##################......####..###....##
###...........####......##############.......####..###....##
###...........####..........##########........##...###....##
###............####..........#########.............####..###
###...........#####...........#######..............#########
###.....##########............######.......##......#########
##.....###########.....###.....####.......####......########
##.....############....###......##.......#####........######
###...##############..#####.............#######.......######
################################...##..#####################
############################################################

There's still no guarantee of connectedness, though. However, it's now
consistently almost-connected, so that you can reasonably just drop the
isolated chunks.

Finally, here is the C program I used to try out different parameters.
Before putting this into an actual game, handling of disconnected
regions is needed.

*/

#include <ghack.h>
#include <gh_maze.h>

static int GH_MAP_WIDTH                 = 40;
static int GH_MAP_HEIGHT                = 40;

static int GH_MAP_FILL_PROB             = 20;
static int GH_MAP_R1                    = 5;
static int GH_MAP_R2                    = 2;
static int GH_MAP_GENERATIONS           = 5;

static int randpick (void)
{
    if ((rand () % 100) < GH_MAP_FILL_PROB) {
        return (GH_MAP_ROCK);
    } else {
        return (GH_MAP_ROOM);
    }
}

//
// Grow our cells
//
void gh_maze::forest_generation (void)
{
    GH_FUNCTION()

    int x, y, i, j;

    for (y=1; y < maze_h-1; y++) {
        for (x=1; x < maze_w-1; x++) {

            int adjcount_r1 = 0,
            adjcount_r2 = 0;

            //
            // Count adjacent room tiles.
            //
            for (i=-1; i <= 1; i++) {
                for (j=-1; j <= 1; j++) {
                    if (map[y+i][x+j] != GH_MAP_ROOM) {
                        adjcount_r1++;
                    }
                }
            }

            for (i=y-2; i <= y+2; i++) {
                for (j=x-2; j <= x+2; j++) {

                    if ((abs(i-y) == 2) && (abs(j-x)==2)) {
                        //
                        // Too close to the edge.
                        //
                        continue;
                    }

                    if (i < 0 || j < 0 || i>=maze_h || j>=maze_w) {
                        //
                        // Out of bounds.
                        //
                        continue;
                    }

                    if (map[i][j] != GH_MAP_ROOM) {
                        adjcount_r2++;
                    }
                }
            }

            //
            // Adjust for the grow threshold for rock or flow.
            //
            if ((adjcount_r1 >= GH_MAP_R1) ||
                (adjcount_r2 <= GH_MAP_R2)) {
                map_save[y][x] = GH_MAP_ROCK;
            } else {
                map_save[y][x] = GH_MAP_ROOM;
            }
        }
    }

    for (y=1; y < maze_h-1; y++) {
        for (x=1; x < maze_w-1; x++) {
            map[y][x] = map_save[y][x];
        }
    }
}

//
// Generate a forest!
//
void gh_maze::make_forest (void)
{
    GH_FUNCTION()

    int x, y, i;

    for (y=1; y < maze_h-1; y++) {
        for (x=1; x < maze_w-1; x++) {
            map[y][x] = randpick();
        }
    }

    for (y=0; y < maze_h; y++) {
        for (x=0; x < maze_w; x++) {
            map_save[y][x] = GH_MAP_ROCK;
        }
    }

    for (y=0; y < maze_h; y++) {
        map[y][0] = map[y][maze_w-1] = GH_MAP_ROCK;
        map[y][0] = map[y][maze_w-2] = GH_MAP_ROCK;
        map[y][0] = map[y][maze_w-3] = GH_MAP_ROCK;
        map[y][0] = map[y][maze_w-4] = GH_MAP_ROCK;
        map[y][0] = map[y][maze_w-5] = GH_MAP_ROCK;
        map[y][0] = map[y][0] = GH_MAP_ROCK;
        map[y][0] = map[y][1] = GH_MAP_ROCK;
        map[y][0] = map[y][2] = GH_MAP_ROCK;
        map[y][0] = map[y][3] = GH_MAP_ROCK;
        map[y][0] = map[y][4] = GH_MAP_ROCK;
    }

    for (x=0; x < maze_w; x++) {
        map[0][x] = map[maze_h-1][x] = GH_MAP_ROCK;
        map[0][x] = map[maze_h-2][x] = GH_MAP_ROCK;
        map[0][x] = map[maze_h-3][x] = GH_MAP_ROCK;
        map[0][x] = map[maze_h-4][x] = GH_MAP_ROCK;
        map[0][x] = map[maze_h-5][x] = GH_MAP_ROCK;
        map[0][x] = map[0][x] = GH_MAP_ROCK;
        map[0][x] = map[1][x] = GH_MAP_ROCK;
        map[0][x] = map[2][x] = GH_MAP_ROCK;
        map[0][x] = map[3][x] = GH_MAP_ROCK;
        map[0][x] = map[4][x] = GH_MAP_ROCK;
    }

    GH_MAP_GENERATIONS = 3 + (rand() % 10);

    for (i=0; i < GH_MAP_GENERATIONS; i++) {
        forest_generation();
    }
}

//
// Generate a maze!
//
void gh_maze::forest_gen (void)
{
    GH_FUNCTION()

    GH_LOG("Generate new forest");

redo:
    maze_w = GH_MIN(GH_MAP_WIDTH + level*2, GH_MAX_MAZE_SIZE - 2);
    maze_h = GH_MIN(GH_MAP_HEIGHT + level*2, GH_MAX_MAZE_SIZE - 2);
    maze_w = GH_MAX(maze_w, GH_MIN_MAZE_SIZE);
    maze_h = GH_MAX(maze_h, GH_MIN_MAZE_SIZE);

    maze_reset();
    memset(map_save, ' ', sizeof(map_save));
    make_forest();

    place_obstacle(GH_MAP_START);
    place_obstacle(GH_MAP_EXIT);

    //
    // More of everything in forests.
    //
    place_monst();
    place_treasure();
    place_potion();
    place_potion();
    place_potion();

    if (!maze_test()) {
        /*
         * No solution for the maze!
         */
        goto redo;
    }

    //
    // Change the floor to dirt!
    //
    for (int y=1; y < maze_h-1; y++) {
        for (int x=1; x < maze_w-1; x++) {
            if (map[y][x] == GH_MAP_ROOM) {
                map[y][x] = GH_MAP_TERRAIN;
            }

            if (map[y][x] == GH_MAP_ROCK) {
                map[y][x] = GH_MAP_TREE;
            }
        }
    }

    maze_print();
}
