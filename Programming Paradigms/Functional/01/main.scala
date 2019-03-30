class Rational(n: Int, d: Int) {
	require(d != 0)
	private val g = gcd(n.abs, d.abs)
	val numer = n / g
  	val denom = d / g
  	def this(n: Int) = this(n, 1)

	def + (that: Rational): Rational = new Rational(numer*that.denom + that.numer*denom, denom*that.denom)
	def + (i: Int): Rational = new Rational(numer + i * denom, denom)

	def - (that: Rational): Rational = new Rational(numer*that.denom-that.numer*denom, denom*that.denom)
	def - (i: Int): Rational = new Rational(numer - i * denom, denom)

	def * (that: Rational): Rational = new Rational(numer*that.numer, denom*that.denom)
	def * (i: Int): Rational = new Rational(numer * i, denom)

	def / (that: Rational): Rational = new Rational(numer*that.denom, denom*that.numer)
	def / (i: Int): Rational = new Rational(numer, denom * i)

	override def toString = numer + "/" + denom
	private def gcd(a: Int, b: Int) : Int = if (b==0) a else gcd(b,a%b)
}

object Main {
	def main(args: Array[String]){
		val x = new Rational(25, 125)

		println("x + 5 =")
		println(x + 5)
		println(' ')

		println("x - 3 =")
		println(x - 3)
		println(' ')

		println("x * 3 =")
		println(x * 3)
		println(' ')

		println("x / 25 =")
		println(x / 25)
	}
}