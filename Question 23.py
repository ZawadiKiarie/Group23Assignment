import matplotlib.pyplot as plt
from matplotlib.patches import Polygon as MplPolygon
from matplotlib.path import Path
import numpy as np

# Define the original polygon vertices
original_vertices = [
    (8, 4),
    (2, 4),
    (0, 8),
    (3, 12),
    (7, 12),
    (10, 8)
]

# Function to scale a polygon by a factor
def scale_polygon(vertices, factor):
    """
    Scales each vertex of the polygon by a given factor.

    vertices: list of (x, y) tuples
    factor: scale factor (float)

    :return: list of scaled (x, y) tuples
    """
    return [(x * factor, y * factor) for x, y in vertices]

# Function to draw and fill a polygon with a color
def draw_filled_polygon(ax, vertices, color):
    """
    Draws a filled polygon on the given axes.

    ax: matplotlib axes
    vertices: list of (x, y) tuples
    color: fill color
    """
    polygon = MplPolygon(vertices, closed=True, facecolor=color, linewidth=1.5)
    ax.add_patch(polygon)

# Function to fill a polygon with asterisks
def fill_with_asterisks(ax, vertices, color='green'):
    """
    Fills the interior of a polygon with asterisks (*).
    ax: matplotlib axes
    vertices: list of (x, y) tuples
    color: color of the asterisks
    """
    # Create a Path from the polygon vertices to test point inclusion
    path = Path(vertices)

    # Get bounding box of the polygon
    min_x = min(x for x, y in vertices)
    max_x = max(x for x, y in vertices)
    min_y = min(y for x, y in vertices)
    max_y = max(y for x, y in vertices)

    # Loop through grid of points and check if inside the polygon
    for x in np.arange(min_x, max_x, 0.5):
        for y in np.arange(min_y, max_y, 0.5):
            if path.contains_point((x, y)):
                ax.text(x, y, '*', fontsize=8, color=color, ha='center', va='center')

# Main plot setup
fig, ax = plt.subplots(figsize=(10, 8))
ax.set_title("Original and Scaled Polygon with Asterisk Fill", fontsize=14)
ax.set_facecolor('white')  # Set background to white
ax.set_aspect('equal')     # Keep aspect ratio equal for X and Y

# Set the coordinate space to show both polygons
ax.set_xlim(-2, 24)
ax.set_ylim(-2, 28)

# (a) Draw and fill the original polygon in Red
draw_filled_polygon(ax, original_vertices, '#FF0000')  # Red fill

# (b) Scale up the polygon by factor of 2
scaled_vertices = scale_polygon(original_vertices, 2)

# (c) Fill the scaled polygon with green asterisks
fill_with_asterisks(ax, scaled_vertices, color='green')

# Draw x and y axes using black lines
ax.axhline(0, color='black', linewidth=1)  # X-axis
ax.axvline(0, color='black', linewidth=1)  # Y-axis

# Add axis labels
ax.set_xlabel("X-axis", fontsize=12)
ax.set_ylabel("Y-axis", fontsize=12)

# Add numerical tick marks for axes
ax.set_xticks(np.arange(-2, 25, 2))
ax.set_yticks(np.arange(-2, 29, 2))

# Show the result
plt.grid(True, which='both', linestyle='--', linewidth=0.3, alpha=0.5)  # Optional: light grid
plt.show()
