//package org.logician.sorta

import scala.util.Random
import scala.math
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

/**
 * Created with IntelliJ IDEA.
 * User: Austin
 * Date: 9/20/13
 * Time: 5:17 AM
 * To change this template use File | Settings | File Templates.
 */
object Sorta {

  val count = 100000

  def main(args: Array[String]) {
    println(s"Testing sorting algorithms on $count items")

    assert(sq(count) <= Long.MaxValue, s"$count is too many items!")

    runTest("BubbleSort", count, bubbleSort)
    runTest("SelectionSort", count, selectionSort)
    runTest("InsertionSort", count, insertionSort)
    runTest("QuickSort", count, quickSort)
    runTest("MergeSort", count, mergeSort)
  }

  def runTest(funcName: String, length: Int, func: (Array[Int]) => Array[Int]) = {
    val array = buildArray(length)

    assert(array.length == length)
    assert(!sorted(array))

    val stanDev = standardDeviation(array)

    val startTime = System.currentTimeMillis()
    val sortedArray = func(array)
    val stopTime = System.currentTimeMillis()

    val isSorted = sorted(sortedArray)

    println(s"Sorting function: $funcName Runtime: ${stopTime - startTime}ms Standard Deviation: $stanDev Sorted: $isSorted")

  }

  def buildArray(length: Int): Array[Int] = {
    val rand = new Random()

    {for(_ <- 0 until length) yield rand.nextInt(length)}.toArray
  }

  def sorted(array: Array[Int]): Boolean = {
    var last = -1

    // If every item is greater than or equal to the last, then the list is sorted.
    array.forall(curr => {
      val isGreater = curr >= last
      last = curr
      isGreater
    })
  }

  def standardDeviation(array: Array[Int]): Double = {
    val nonSqMean = mean(array)
    val diffSqArray:Array[Long] = array.map(int => sq(int.toLong - nonSqMean))

    math.sqrt(mean(diffSqArray))
  }

  def sq(long: Long) = long * long

  def mean(array: Array[Long]): Long = array.sum / array.length

  def mean(array: Array[Int]): Int = array.sum / array.length

  def bubbleSort(array: Array[Int]): Array[Int] = {
    var didSwap = false

    for(i <- 0 until array.length - 1)
      if(array(i+1) < array(i)){
        val temp = array(i)
        array(i) = array(i+1)
        array(i+1) = temp
        didSwap = true
      }

    // Repeat until we don't have anymore swaps
    if(didSwap)
      bubbleSort(array)
    else
      array
  }

  def selectionSort(array: Array[Int]): Array[Int] = {
    for(i <- 0 until array.length){
      var minPos = i

      for(j <- i+1 until array.length)
        if(array(j) < array(minPos))
          minPos = j

      if(minPos != i){
        val temp = array(i)
        array(i) = array(minPos)
        array(minPos) = array(i)
      }
    }

    array
  }

  def insertionSort(array: Array[Int]): Array[Int] = {

    for(i <- 0 until array.length){

      val hold = array(i)
      var holePos = i

      while(holePos > 0 && hold < array(holePos - 1)){
        array(holePos) = array(holePos - 1)
        holePos -= 1
      }

      array(holePos) = hold
    }

    array
  }

  def quickSort(array: Array[Int]): Array[Int] = {
    if(array.length <= 1)
      return array

    val arrBuff = array.toBuffer

    val pivot = selectPivot(array)

    arrBuff -= pivot

    val (less, greater) = arrBuff.toArray.partition(_ <= pivot)

    Array.concat(quickSort(less), Array(pivot), quickSort(greater))
  }

  def selectPivot(array: Array[Int]): Int = {
    val first = array.head
    val middle = array(array.length / 2)
    val last = array.last

    math.max(math.max(first, middle), last) match {
      case `first` => math.max(middle, last)
      case `middle` => math.max(first, last)
      case `last` => math.max(first, middle)
    }
  }

  def mergeSort(array: Array[Int]): Array[Int] = {
    if(array.length <= 1)
      return array

    val (left, right) = array.splitAt(array.length / 2)

    val leftSorted = mergeSort(left)
    val rightSorted = mergeSort(right)

    merge(leftSorted, rightSorted)
  }

  def merge(leftArr: Array[Int], rightArr: Array[Int]): Array[Int] = {
    var left = leftArr
    var right = rightArr

    var leftHead, rightHead = 0

    var result = new mutable.ArrayBuffer[Int]()

    while(!left.isEmpty && !right.isEmpty){
      leftHead = left.head
      rightHead = right.head

      if(leftHead <= rightHead){
        result += leftHead        
        left = left.tail
      } else {
        result += rightHead
        right = right.tail
      }
    }

    if(!left.isEmpty)
      result ++= left
    else if (!right.isEmpty)
      result ++= right

    result.toArray
  }
}