package main


func main() {
	println("adding two numbers in golang:", 2*3)
}

//export main
func alc() {
	println("adding two numbers in golang:", 2*3) // expecting 5
}
