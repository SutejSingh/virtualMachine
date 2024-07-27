# Virtual Machine
Virtual Machine written in C++ that can execute ASM-like code and draw bitmaps using a turtle drawer

## Registers

The machine supports the following registers:
| Register	| Note |
|-----------|-------|
| r0 |Always zero (constant) |
|r1, r2, r3, r4, r5, r6, r7	| Seven general purpose registers|
|pc |	Program counter (keeps track of next op to execute) |
| sc | Stack count (keeps track of number of integers on the stack |
| ex | Stores the exception code |
|tx, ty |	These are the x, y positions of the turtle |
|tr |	Stores the rotation of the turtle, in degrees |
| tc |	Stores draw color for the turtle |

## Flags

The VM supports the following flags
|Flag |	Note |
|-----|------|
| exit | If true, program should exit |
| test | Used for conditional jumps |
| pen | If true, turtle moving forward/backwards draws |

## Operations

The VM supports the following operations
| Op | Parameters | Behavior |
|----|------------|----------|
| movi |	reg1,int |	Sets reg1 = int |
| add |	reg1,reg2,reg3 |	reg1 = reg2 + reg3 |
| mov |	reg1,reg2 |	Sets reg1 = reg2 |
| sub |	reg1,reg2,reg3 |	reg1 = reg2 - reg3 |
| mul |	reg1,reg2,reg3 |	reg1 = reg2 * reg3 |
| div |	reg1,reg2,reg3 |	reg1 = reg2 / reg3 |
| inc |	reg1 |	reg1++ |
| dec |	reg1 |	reg1-- |
| jmp |	reg1 |	Sets pc = reg1 |
| cmpeq |	reg1,reg2 |	Sets test flag = (reg1 == reg2) |
| cmplt	| reg1,reg2 |	Sets test flag = (reg1 < reg2) |
| jt | reg1 |	If test == true, then set pc = reg1 (otherwise don’t do anything) |
| jnt |	reg1 |	If test == false, then set pc = reg1 (otherwise don’t do anything) |
| push |	reg1 |	Pushes reg1 onto stack, and increments the sc register |
| pop |	reg1 |	Pops top of stack into reg1, and decrements the sc register |
| load |	reg1,reg2 |	reg1 = stack[reg2] |
| store |	reg1,reg2 |	stack[reg1] = reg2 |
| loadi |	reg1,int |	reg1 = stack[int] |
| store |	int,reg1 |	stack[int] = reg1|
| loadsc |	reg1,reg2 |	reg1 = stack[sc – reg2 – 1] |
| storesc |	reg1,reg2 |	stack[sc – reg1 – 1] = reg2 |
| pendown |	(No parameters) |	Sets “pen” flag to true |
| penup |	(No parameters) |	Sets “pen” flag to false |
| fwd |	reg1 | Moves turtle forward reg1 units from current (tx, ty) position, taking into account any rotation from tr. Draws a line for this movement if pen == true |
| back | reg1 |	Moves turtle backwards reg1 units from current (tx, ty) position, taking into account any rotation from tr. Draws a line for this movement if pen == true |

## Supported Turtle Color Values
The following colors are supported for drawing with turtle
| tc value | Color |
|-----------|-------|
| 0 |	White = (255, 255, 255) |
| 1 |	Yellow = (255, 255, 0) |
| 2 |	Magenta = (255, 0, 255)|
| 3 |	Red = (255, 0, 0)|
| 4	| Cyan = (0, 255, 255) |
| 5 |	Green = (0, 255, 0) |
| 6 |	Blue = (0, 0, 255) |
| 7 |	Black = (0, 0, 0)|
