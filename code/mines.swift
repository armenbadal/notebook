class Cell: CustomStringConvertible {
    enum State: Int {
        case Closed   // փակ
        case Open     // բաց
        case Flagged  // նշված
    }

    var state = State.Closed  // վիճակ
    var hasMine = false       // ական
    var minesAround = 0       // հարևան ականներ

    // տեքստային ներկայացում
    var description: String {
        if self.state == .Closed {
            return "?"
        }

        if self.state == .Flagged {
            return "P"
        }

        if self.hasMine {
            return "*"
        }

        return 0 == minesAround ? "." : String(minesAround)
    }
}

class Field {
    let rows: Int        // տողերի քանակը
    let columns: Int     // սյուների քանակը
    var cells: [[Cell]]  // ականադաշտի մատրիցը
    let minesCount: Int  // ականների քանակը

    init(rows: Int, columns: Int) {
        self.rows = rows
        self.columns = columns

        // մատրիցի ստեղծելը
        cells = (0..<rows).map { _ in (0..<columns).map { _ in Cell() } }

        // ականների տեղադրելը
        minesCount = rows * columns * 15 / 100
        for _ in 0..<minesCount { 
            let r = Int.random(in: 0..<rows)
            let c = Int.random(in: 0..<columns)
            self.cells[r][c].hasMine = true
        }

                // հաշվել ամեն մի բջջի հարևան ականները
        let rcix = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
        for r in 0..<self.rows {
            for c in 0..<self.columns {
                if self.cells[r][c].hasMine {
                    continue
                }

                var count = 0
                for (dr, dc) in rcix {
                    let nr = r + dr
                    let nc = c + dc
                    if self.cells[nr][nc].hasMine {
                        count += 1
                    }
                }
                self.cells[r][c].minesAround = count
            }
        }
    }


    func show() {
        for r in 0..<self.rows {
            for c in 0..<self.columns {
                print(self.cells[r][c], terminator: " ")
            }
            print("")
        }
    }
}
