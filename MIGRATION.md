# libcoda-dice → Seamwork

**Disposition: ABSORB selectively.** Generic dice behavior and Yahtzee domain logic were historically combined here. The meaningful interface question—testable randomness, ownership, and retained dice—was rebuilt as a small C++23 [Seamwork Yahtzee randomness study](https://github.com/ryjen/seamwork/tree/development/studies/yahtzee-randomness). It is **not** a direct port or API-compatible replacement.

## Historical provenance

- Original repository: https://github.com/ryjen/libcoda-dice
- Exact revision pinned in the former aggregate: [`4802a244a71186991057a3c71ce33a783c7b6277`](https://github.com/ryjen/libcoda-dice/commit/4802a244a71186991057a3c71ce33a783c7b6277)
- Primary migration record: https://github.com/ryjen/seamwork/blob/development/docs/migration/seamwork-rebrand.md
- Primary tracking issue: https://github.com/ryjen/seamwork/issues/34

The old `coda::die`, `coda::dice`, and Yahtzee score classes stay here for code/history comparison. They are not promoted as a supported component. Historical source, tests, and original license remain in this repository. New code should be consumer-driven and use Seamwork's C++23 design process.

The old raw-pointer engine lifetime, mutable side-count invariant and default global engine were intentionally *not* carried forward. See the Seamwork study README and QART for the comparison.

No maintained GitHub Actions CI is defined for this historical repository. Do not rename old APIs in place simply to match Seamwork's identity.
