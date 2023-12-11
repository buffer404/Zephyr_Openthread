import * as console from './wamr_app_lib/console'

export function app_main(argc: i32, argv: Array<u32>): i32 {
    var n = 5
    console.log("num is ")
    console.log(n.toString())
    var a = 0, b = 1
    if (n > 0) {
      while (--n) {
        let t = a + b
        a = b
        b = t
      }
      return b
    }
    // return a
    console.log("fib =")
    console.log(a.toString())
    // argv[0] = a
    return a
    }
