import scala.collection.mutable.Map

class ChecksumAccumulator{
	private var sum = 0
	def add(b: Byte){sum += b}
	def checksum(): Int = sum
}

object ChecksumAccumulator{
	private val cache = Map[String, Int]()

	def calculate(s: String): Int =
		if (cache.contains(s))
			cache(s)
		else{
			val acc = new ChecksumAccumulator
			for (c <- s)
				acc.add(c.toByte)
			val cs = acc.checksum()
			cache += (s -> cs)
			cs
		}
}

object main extends App {
	for (season <- List("fall", "winter", "spring"))
		println(season + ": " + ChecksumAccumulator.calculate(season))
}