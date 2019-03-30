//Palm muting is a guitar technic used in Metal that allows to keep a clean sound after each note
//Vocanulary: "PLUCKED" == "PLAYED"
//It must always be used wether the next note has to be plucked or not
//If note has to be played -> pluck it and palm it
//If note should not be played -> do not pluck, just palm it

object Assignment{
  def main(args: Array[String]){

    //List of notes that have to be plucked or not
    val notesToPluck = List(true, true, false)
    //List of notes that have been plucked after been checked for pluckability
    var palmedNotes = List(false, false, false)

    println("notes to pluck ", notesToPluck)
    println("notes to palm ", palmedNotes)

    //calling control Structure
    palmedNotes = metalPlay(notesToPluck)(palmedNotes)(pluck)

    //Showing final Output
    println("Palmed notes after metalPlay ", palmedNotes)
  }

  //Control Structure
  def metalPlay(notes: List[Boolean])(palmed: List[Boolean])(plucker: Boolean => Boolean) : List[Boolean] = {
    var newPalmedNotes = palmed
    for(i <- 0 to 2){
      try{
        plucker(notes(i))
      }
      finally{
        //note always palmed no matter what
        newPalmedNotes = newPalmedNotes.updated(i, true)
        println("Note has been palm muted")
      }
    }
    newPalmedNotes
  }

  //functions that checks if a note should be plucked/played or not
  def pluck(toPluck: Boolean) : Boolean = {
    if(toPluck){
      println("Note plucked")
    }
    else{
      println("Note NOT plucked")
    }
    toPluck
  }
}
