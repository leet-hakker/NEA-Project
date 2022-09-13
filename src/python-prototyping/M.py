from numbers import Rational
from fractions import Fraction

class M(Rational):
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

		return True

	def __lt__(self, other):
		if isinstance(other, M):
			return (self.m_val > other.m_val) or (self.m_val == other.m_val and
												  self.num_val > other.num_val)
		return False

	def __gte__(self, other):
		if isinstance(other, M):
			return (self.m_val >= other.m_val) or (self.m_val == other.m_val and
												  self.num_val >= other.num_val)

		return True

	def __lte__(self, other):
		if isinstance(other, M):
			return (self.m_val <= other.m_val) or (self.m_val == other.m_val and
												  self.num_val <= other.num_val)

		return False

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
		return self
	

	def __div__(self, other):
		if isinstance(other, M):
			self.m_val *= other.m_val
			self.num_val *= other.num_val
			return self
		self.num_val *= other
		return self
	
	def __abs__(self):
		pass
	
	def __ceil__(self):
		pass
	
	def __floor__(self):
		pass
	
	def __floordiv__(self, other):
		pass
	
	def __le__(self, other):
		pass
	
	def __mod__(self, other):
		pass
	
	def __neg__(self):
		pass
	
	def __pos__(self):
		pass
	
	def __pow__(self):
		pass
	
	def __radd__(self):
		pass
	
	def __rfloordiv__(self, other):
		pass
	
	def __rmod__(self, other):
		pass
	
	def __rmul__(self, other):
		pass
	
	def __round__(self, other):
		pass
	
	def __rpow__(self, other):
		pass
	
	def __rtruediv__(self, other):
		pass
	
	def __truediv__(self, other):
		pass
	
	def __trunc__(self):
		pass
	
	@property
	def denominator(self):
		if self.m_val != 0:
			return self.m_val.denominator
		return self.num_val.denominator
	
	@property
	def numerator(self):
		if self.m_val != 0:
			return self.m_val.numerator
		return self.num_val.numerator
