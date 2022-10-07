from numbers import Number
from fractions import Fraction


class M(Number):
    # M class is a number with two values.
    # One regular number value, and another Big M value.
    def __init__(self, num_val, m_val):
        self.num_val = Fraction(num_val)
        self.m_val = Fraction(m_val)

    def __repr__(self):
        if self.m_val != 0:
            if self.m_val < 0:
                return f"({self.num_val} - {abs(self.m_val)}M)"
            return f"({self.num_val} + {self.m_val}M)"
        else:
            return f"{self.num_val}"

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
        
        return self.m_val == 0 and self.num_val == other

    def __add__(self, other):
        new = M(0, 0)
        if isinstance(other, M):
            new.m_val = self.m_val + other.m_val
            new.num_val = self.num_val + other.num_val
            return new
        new.num_val = self.num_val + other
        new.m_val = self.m_val
        return new


    def __sub__(self, other):
        new = M(0, 0)
        if isinstance(other, M):
            new.m_val = self.m_val - other.m_val
            new.num_val = self.num_val - other.num_val
            return new
        new.num_val = self.num_val - other
        new.m_val = self.m_val
        return new

    def __mul__(self, other):
        new = M(0, 0)
        if isinstance(other, M):
            new.m_val = self.m_val * other.m_val
            new.num_val = self.num_val * other.num_val
            return new
        new.num_val = self.num_val * other
        new.m_val = self.m_val *other
        return new

    def __div__(self, other):
        new = M(0, 0)
        if isinstance(other, M):
            new.m_val = self.m_val / other.m_val
            new.num_val = self.num_val / other.num_val
            return new
        new.num_val = self.num_val / other
        new.m_val = self.m_val / other
        return new

    def __neg__(self):
        return M(-self.num_val, -self.m_val)
