-- phpMyAdmin SQL Dump
-- version 5.2.3
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jan 20, 2026 at 04:42 PM
-- Server version: 5.7.44-log
-- PHP Version: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `frisa`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `id_admin` int(11) NOT NULL,
  `nama_admin` varchar(100) NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`id_admin`, `nama_admin`, `username`, `password`) VALUES
(1, 'Dobilion', 'Dobilion', 'dobi123'),
(7, 'Doni Marlopo', 'DoniMarlopo', 'donilopo12,'),
(8, 'Dominian', 'dominian', 'dominian12,');

-- --------------------------------------------------------

--
-- Table structure for table `ambulans`
--

CREATE TABLE `ambulans` (
  `id_ambulans` int(11) NOT NULL,
  `plat_nomor` varchar(15) NOT NULL,
  `id_supir` int(11) DEFAULT NULL,
  `status` enum('TERSEDIA','DIPAKAI') DEFAULT 'TERSEDIA'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ambulans`
--

INSERT INTO `ambulans` (`id_ambulans`, `plat_nomor`, `id_supir`, `status`) VALUES
(2, 'BA 1950 K', 2, 'DIPAKAI'),
(3, 'BK 1920 F', NULL, 'TERSEDIA'),
(6, 'BZ 1890 K', 8, 'TERSEDIA');

-- --------------------------------------------------------

--
-- Table structure for table `laporan`
--

CREATE TABLE `laporan` (
  `id_laporan` int(11) NOT NULL,
  `id_user` int(11) NOT NULL,
  `id_ambulans` int(11) NOT NULL,
  `id_supir` int(11) NOT NULL,
  `id_rs` int(11) NOT NULL,
  `tanggal` datetime DEFAULT CURRENT_TIMESTAMP,
  `biaya` int(11) DEFAULT '0',
  `status_laporan` enum('MENUNGGU_SUPIR','DITOLAK_SUPIR','DIPROSES','SELESAI') DEFAULT 'MENUNGGU_SUPIR'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `laporan`
--

INSERT INTO `laporan` (`id_laporan`, `id_user`, `id_ambulans`, `id_supir`, `id_rs`, `tanggal`, `biaya`, `status_laporan`) VALUES
(3, 4, 2, 2, 2, '2026-01-20 12:38:30', 0, 'MENUNGGU_SUPIR');

-- --------------------------------------------------------

--
-- Table structure for table `rumah_sakit`
--

CREATE TABLE `rumah_sakit` (
  `id_rs` int(11) NOT NULL,
  `nama_rs` varchar(100) NOT NULL,
  `alamat` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `rumah_sakit`
--

INSERT INTO `rumah_sakit` (`id_rs`, `nama_rs`, `alamat`) VALUES
(1, 'RSUD Kota', 'Jl. Merdeka No.1'),
(2, 'RS Sejahtera', 'Jl. Kesehatan No.10'),
(3, '', 'd'),
(4, 'Rs Aisyah', 'Jl, Siti Manggopo');

-- --------------------------------------------------------

--
-- Table structure for table `supir`
--

CREATE TABLE `supir` (
  `id_supir` int(11) NOT NULL,
  `nama_supir` varchar(100) NOT NULL,
  `no_hp` varchar(15) DEFAULT NULL,
  `email` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `supir`
--

INSERT INTO `supir` (`id_supir`, `nama_supir`, `no_hp`, `email`, `password`) VALUES
(2, 'Dodi Bido', '081375604933', 'dodoibido@gmail.com', 'dodibido12,'),
(8, 'Boger Bojinof', '085314958870', 'boger12@gmail.com', 'bogerjago12,');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `id_user` int(11) NOT NULL,
  `nik` varchar(16) NOT NULL,
  `nama` varchar(100) NOT NULL,
  `tanggallahir` date NOT NULL,
  `bpjs` enum('BPJS','NON BPJS') NOT NULL,
  `nohp` varchar(14) NOT NULL,
  `email` varchar(30) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id_user`, `nik`, `nama`, `tanggallahir`, `bpjs`, `nohp`, `email`, `password`) VALUES
(4, '1377010710060001', 'Dede Jurnal Kurniadi', '2006-10-07', 'BPJS', '085351359181', 'dejur0590@gmail.com', 'dedeganteng0590,'),
(5, '1399058092340007', 'Zaki Ahmad', '2007-12-12', 'NON BPJS', '081378840590', 'zakitandun@gmail.com', 'zakimaks12,'),
(6, '1389250404080001', 'Bhas Ambabas Ambalacang', '2000-12-07', 'NON BPJS', '085351359181', 'ambalabas@gmail.com', 'ambalabas12,'),
(7, '1377010710060000', 'Guido Lumoindong Gilbert', '2006-07-07', 'NON BPJS', '081378840590', 'guido12@gmail.com', 'guido12,'),
(8, '1377890567899290', 'Dilantak Oto', '2012-07-07', 'BPJS', '085163768546', 'dilan12@gmail.com', 'dilan12,');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id_admin`),
  ADD UNIQUE KEY `username` (`username`);

--
-- Indexes for table `ambulans`
--
ALTER TABLE `ambulans`
  ADD PRIMARY KEY (`id_ambulans`),
  ADD UNIQUE KEY `plat_nomor` (`plat_nomor`),
  ADD UNIQUE KEY `plat_nomor_2` (`plat_nomor`),
  ADD KEY `id_supir` (`id_supir`);

--
-- Indexes for table `laporan`
--
ALTER TABLE `laporan`
  ADD PRIMARY KEY (`id_laporan`),
  ADD KEY `id_user` (`id_user`),
  ADD KEY `id_ambulans` (`id_ambulans`),
  ADD KEY `id_supir` (`id_supir`),
  ADD KEY `id_rs` (`id_rs`);

--
-- Indexes for table `rumah_sakit`
--
ALTER TABLE `rumah_sakit`
  ADD PRIMARY KEY (`id_rs`);

--
-- Indexes for table `supir`
--
ALTER TABLE `supir`
  ADD PRIMARY KEY (`id_supir`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id_user`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `id_admin` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `ambulans`
--
ALTER TABLE `ambulans`
  MODIFY `id_ambulans` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `laporan`
--
ALTER TABLE `laporan`
  MODIFY `id_laporan` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `rumah_sakit`
--
ALTER TABLE `rumah_sakit`
  MODIFY `id_rs` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `supir`
--
ALTER TABLE `supir`
  MODIFY `id_supir` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id_user` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ambulans`
--
ALTER TABLE `ambulans`
  ADD CONSTRAINT `ambulans_ibfk_1` FOREIGN KEY (`id_supir`) REFERENCES `supir` (`id_supir`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `laporan`
--
ALTER TABLE `laporan`
  ADD CONSTRAINT `laporan_ibfk_1` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE CASCADE,
  ADD CONSTRAINT `laporan_ibfk_2` FOREIGN KEY (`id_ambulans`) REFERENCES `ambulans` (`id_ambulans`) ON DELETE CASCADE,
  ADD CONSTRAINT `laporan_ibfk_3` FOREIGN KEY (`id_supir`) REFERENCES `supir` (`id_supir`) ON DELETE CASCADE,
  ADD CONSTRAINT `laporan_ibfk_4` FOREIGN KEY (`id_rs`) REFERENCES `rumah_sakit` (`id_rs`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
