import pygame
import logging
import numpy as np
from union import eff_union

logging.basicConfig(filename='test.log', level=logging.INFO, format='%(asctime)s:%(levelname)s:%(message)s')
pygame.init()

class gameboard:
    def __init__(self, size=64, prob = 0.5):
        self.prob = prob
        self.size = size
        self.board = np.random.choice([0, 1], size=(self.size, self.size), p=[1 - self.prob, self.prob])

    def open_cell(self, position):
        self.board[position[0]][position[1]] = 1

    def get_board(self):
        return self.board

    def regen(self, size = None):
        self.size = size if size != None else self.size
        self.board = np.random.randint(low = 0, high = 2, size = (self.size, self.size))

    def xy_to_num(self, x, y):
        return y * self.size + x # NOTE: input in cartesian form (c, r) or (x, y)

    def num_to_xy(self, num):
        y = num // self.size
        x = num - y * self.size
        return (y, x) # NOTE: returning in array compatible form (r, c)

    def get_open_nodes(self):
        open_idx = []
        for r in range(self.size):
            for c in range(self.size):
                if self.board[r][c] != 0:
                    open_idx.append(self.xy_to_num(c, r))
        return open_idx

SIZE = SCREEN_W, SCREEN_H = (512, 512 + 30)
SCREEN = pygame.display.set_mode(SIZE)
MSGBOX = pygame.Surface.subsurface(SCREEN, (0, 512, SCREEN_W, 30))
pygame.display.set_caption("Percolation Demo")

# set up fonts
font = pygame.font.SysFont('Arial', 20)

FPS = 30
clock = pygame.time.Clock()

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (100, 100, 205)
sep_width = 2

def draw_grid(board, size = 64):
    blockSize = SCREEN_W // size # Set the size of the grid block
    for x in range(size):
        for y in range(size):
            start_x = x * blockSize
            start_y = y * blockSize
            rect = pygame.Rect(start_x, start_y, blockSize - sep_width, blockSize - sep_width)
            color = WHITE if board[y][x] else BLUE
            pygame.draw.rect(SCREEN, color, rect)

is_running = True
size = 16
gb = gameboard(size, prob = 0.595)

# union data structure
qu = eff_union(size * size + 2) # size = top node, size + 1 = bottom node

def update_tree(gameboard, ds, size):
    open_nodes = gameboard.get_open_nodes()

    logging.info(f"open nodes list: {open_nodes}")

    for idx in open_nodes:
        # connect first line with top node
        if idx in range(0, size):
            ds.union_op(size * size, idx)

        # connect last line with bottom node
        elif idx in range(size * (size - 1), size ** 2):
            ds.union_op(size * size + 1, idx)

        else:
            pos = gameboard.num_to_xy(idx)
            dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)] # bottom, up, right, left
            for d in dirs:
                r_pos = pos[0] + d[0]
                c_pos = pos[1] + d[1]
                if c_pos < 0 or c_pos > size - 1: # ignore adjacent edge cells
                    continue
                if gameboard.board[r_pos, c_pos]:
                    adj_idx = gameboard.xy_to_num(c_pos, r_pos)
                    ds.union_op(idx, adj_idx)

    logging.info(f"current state: {qu}")

update_tree(gb, qu, size)

# percolate?
res = qu.connected(size * size, size * size + 1)
text = font.render(f"Percolates: {res}", 1, BLACK)

while is_running:
    SCREEN.fill(BLACK)
    MSGBOX.fill(WHITE)
    SCREEN.blit(text, (10, 515))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            is_running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_r:
                # reset the gameboard
                size = np.random.choice([8, 16, 32, 64])
                gb.regen(size)
                qu = eff_union(size * size + 2)
                update_tree(gb, qu, size)
                res = qu.connected(size * size, size * size + 1)
                text = font.render(f"Percolates: {res}", 1, BLACK)
    draw_grid(gb.get_board(), gb.size)
    clock.tick(FPS)

    pygame.display.update()
pygame.quit()
