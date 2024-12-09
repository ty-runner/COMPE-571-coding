import sys
import random

class PageReplacement:
    @staticmethod
    def random_replacement(page_table):
        return random.choice(list(page_table.keys()))

    @staticmethod
    def fifo_replacement(queue):
        return queue.pop(0)

    @staticmethod
    def lru_replacement(page_table):
        return min(page_table.items(), key=lambda x: x[1].last_used)[0]

    @staticmethod
    def periodic_reset_replacement(page_table, ref_reset_interval):
        """
        Periodic reset implementation for page reference bits.
        """
        unreferenced_clean = [p for p, e in page_table.items() if not e.referenced and not e.dirty]
        if unreferenced_clean:
            return unreferenced_clean[0]

        # Add more categories if needed
        return next(iter(page_table))  # Fallback

class PageTableEntry:
    def __init__(self, frame_number=None, dirty=False, referenced=False):
        self.frame_number = frame_number
        self.dirty = dirty
        self.referenced = referenced
        self.last_used = -1  # For LRU tracking

class PageTable:
    def __init__(self, process_id):
        self.process_id = process_id
        self.entries = {}

    def get_entry(self, page_number):
        if page_number not in self.entries:
            self.entries[page_number] = PageTableEntry()
        return self.entries[page_number]

class VirtualMemorySimulation:
    def __init__(self, memory_references):
        self.memory_references = memory_references
        self.page_tables = {}
        self.page_frames = {}
        self.stats = {"page_faults": 0, "disk_accesses": 0, "dirty_writes": 0}
        self.queue = []

    def run(self, algorithm):
        self.stats = {"page_faults": 0, "disk_accesses": 0, "dirty_writes": 0}
        time = 0

        for process_id, address, op in self.memory_references:
            virtual_page = address // 512  # Virtual page number
            page_table = self.page_tables.setdefault(process_id, PageTable(process_id))
            entry = page_table.get_entry(virtual_page)

            if entry.frame_number is None:
                self.handle_page_fault(page_table, virtual_page, op, algorithm)
            else:
                if op == "W":
                    entry.dirty = True
            entry.referenced = True
            entry.last_used = time
            time += 1

    def handle_page_fault(self, page_table, virtual_page, op, algorithm):
        self.stats["page_faults"] += 1
        self.stats["disk_accesses"] += 1

        # Page replacement logic
        if len(self.page_frames) >= 32:
            if algorithm == "RAND":
                victim_page = PageReplacement.random_replacement(self.page_frames)
            elif algorithm == "FIFO":
                victim_page = PageReplacement.fifo_replacement(self.queue)
            elif algorithm == "LRU":
                victim_page = PageReplacement.lru_replacement(self.page_frames)
            elif algorithm == "PER":
                victim_page = PageReplacement.periodic_reset_replacement(self.page_frames, 200)
            else:
                raise ValueError(f"Unknown algorithm: {algorithm}")

            self.evict_page(victim_page)

        frame_number = len(self.page_frames)
        self.page_frames[virtual_page] = frame_number
        self.queue.append(virtual_page)
        page_table.entries[virtual_page].frame_number = frame_number

        if op == "W":
            page_table.entries[virtual_page].dirty = True

    def evict_page(self, victim_page):
        for process_table in self.page_tables.values():
            entry = process_table.entries.get(victim_page)
            if entry and entry.frame_number is not None:
                if entry.dirty:
                    self.stats["dirty_writes"] += 1
                    self.stats["disk_accesses"] += 1
                entry.frame_number = None
                break
        self.page_frames.pop(victim_page, None)


    def report(self):
        print(f"Page Faults: {self.stats['page_faults']}")
        print(f"Disk Accesses: {self.stats['disk_accesses']}")
        print(f"Dirty Page Writes: {self.stats['dirty_writes']}")


def load_memory_references(file_path):
    """
    Reads memory references from an input file.
    Returns a list of tuples: (process_number, memory_address, operation).
    """
    references = []
    with open(file_path, "r") as f:
        for line in f:
            process, address, op = line.strip().split()
            references.append((int(process), int(address), op))
    return references


def main():
    if len(sys.argv) != 2:
        print("Usage: python virtual_memory_simulation.py <input_file>")
        sys.exit(1)
    memory_references = load_memory_references(sys.argv[1])

    simulation = VirtualMemorySimulation(memory_references)

    algorithms = ["RAND", "FIFO", "LRU", "PER"]
    for algorithm in algorithms:
        print(f"Running simulation with {algorithm} algorithm:")
        simulation.run(algorithm)
        simulation.report()


if __name__ == "__main__":
    main()