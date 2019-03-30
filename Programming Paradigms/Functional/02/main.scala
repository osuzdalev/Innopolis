object main{
  //external variable for all functions
  var limit = 5

  def main(args: Array[String]) {

    for( x <- 1 to 4){
      println("Iteration ", x)
      println()
      //change value of limit to get different results
      limit += x
      //generate list
      val list = List.range(0, 25)
      println("Generated list")
      println(list)
      println()

      //apply functions on list
      val multiplier_2 = makeMultiplier(limit)
      val check = list.map(s => cutter(multiplier_2(s)))
      val check_true = check.filter(s => remover(s))

      //print out the result
      println("List after use of function 'Cutter' and closure 'multiplier' ")
      println(check)
      println()
      println("List after use of function 'Remover' ")
      println(check_true)
      println()
    }
  }
  //returns a closure
  def makeMultiplier(factor: Int) = (x: Int) => x * factor
  //apply to each elements of list
  def cutter(y: Int) : Int = if (y < limit) y else limit
  //checks all elements of list
  def remover(z: Int) : Boolean = if (z < limit) true else false
}