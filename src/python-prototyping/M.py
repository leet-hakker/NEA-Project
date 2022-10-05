from numbers import Number
from fractions import Fraction


class M(Number):
    # M class is a number with two values.
    # One regular number value, and another Big M value.
    def __init__(self, num_val, m_val):
        self.num_val = Fraction(num_val)
        self.m_val = Fraction(m_val)

    def __repr__(self):
        if self.m_val < 0:
            return f"({self.num_val} - {abs(self.m_val)}M)"
        return f"({self.num_val} + {self.m_val}M)"

    def __gt__(self, other):
        if isinstance(other, M):
            return (self.m_val > other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val > other.num_val)

        return self.m_val > 0

    def __lt__(self, other):
        if isinstance(other, M):
            return (self.m_val < other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val < other.num_val)

        return self.m_val < 0

    def __gte__(self, other):
        if isinstance(other, M):
            return (self.m_val >= other.m_val) or (
                self.m_val == other.m_val and self.num_val >= other.num_val)

        return self.m_val > 0

    def __lte__(self, other):
        if isinstance(other, M):
            return (self.m_val <= other.m_val) or (
                self.m_val == other.m_val and self.num_val <= other.num_val)

        return self.m_val < 0

    def __eq__(self, other):
        if isinstance(other, M):
            return self.m_val == other.m_val and self.num_val == other.num_val
        return False

    def __add__(self, other):
        if isinstance(other, M):
            self.m_val += other.m_val
            self.num_val += other.num_val
            return self
        self.num_val += other
        return self

    def __sub__(self, other):
        if isinstance(other, M):
            self.m_val -= other.m_val
            self.num_val -= other.num_val
            return self
        self.num_val -= other
        return self

    def __mul__(self, other):
        if isinstance(other, M):
            self.m_val *= other.m_val
            self.num_val *= other.num_val
            return self
        self.num_val *= other
        self.m_val *= other
        return self

    def __div__(self, other):
        if isinstance(other, M):
            self.m_val *= other.m_val
            self.num_val *= other.num_val
            return self
        self.num_val *= other
        self.m_val *= other
        return self

    def __neg__(self):
        return M(-self.num_val, -self.m_val)
