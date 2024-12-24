from Vector3 import Vector3

class Color(Vector3):
    def __init__(self, *args):
        super().__init__(*args)
        self._clamp()

    def _clamp(self):
        for i in range(3):
            self.arr[i] = min(max(self.arr[i], 0), 1)
    
    def __add__(self, other):
        return Color(super().__add__(other))
    
    def __mul__(self, other):
        return Color(super().__mul__(other))

    def to_255(self):
        return tuple(int(255.99 * c) for c in self.arr)
